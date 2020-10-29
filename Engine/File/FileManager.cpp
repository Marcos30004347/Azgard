#include "FileManager.hpp"

using namespace Azgard;

#ifndef AZGARD_FILE_SYSTEM_THREADS
#define AZGARD_FILE_SYSTEM_THREADS 3
#endif



char* replaceChar(const char* path, char a, char b) {
    unsigned int n = Azgard::cStrLen(path);
    char* buff = AZG_NEW char[n + 1];
    for(int i=0; i<n; i++) {
        if(path[i] != a) buff[i] = path[i];
        else buff[i] = b;
    }
    buff[n] = '\0';
    return buff;
}


void FileManager::syncOpen(FileHandle& handle, FileHandle::Path path, int fileMode) {
    AZG_DEBUG_SCOPE;


    int mode = 0;

    if(fileMode & FileMode::read) {
        mode |= std::ios::in;
    }
    if(fileMode & FileMode::write) {
        mode |= std::ios::out;
    }
    if(fileMode & FileMode::binary) { 
        mode |= std::ios::binary; 
    }
    if(fileMode & FileMode::atEnd) {
        mode |= std::ios::ate;
    }
    if(fileMode & FileMode::truncate) {
        mode |= std::ios::trunc;
    }
    if(fileMode & FileMode::append) {
        mode |= std::ios::app;
    }

    #ifdef AZGARD_WINDOWS_PLATFORM
    char* file_path = replaceChar(path, '/', '\\');
    #else
    char* file_path = replaceChar(path.value(), '/', '/');
    #endif
    handle.stream.fileStream->open((const char*)file_path, (std::ios_base::openmode)mode);
    delete file_path;
}

void FileManager::syncClose(FileHandle& file) {
    AZG_DEBUG_SCOPE;
    AZG_CORE_ASSERT_AND_REPORT(file.isOpen(), "File %s isn't open!", file.stream.name.value());
    file.stream.fileStream->close();
    delete file.stream.fileStream;
    file.stream.fileStream = nullptr;
}

void FileManager::startUp() {
    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "File Manager Starting...");

    FileManager::gInstancePtr = AZG_NEW FileManager();

    while(FileManager::getSingletonPtr()->startedWorkers.load() != AZGARD_FILE_SYSTEM_THREADS) {
        Azgard::Thread::thisThread::yield();
    }

    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "File Manager Started...");
}

FileManager::FileManager() {
    manager_lock.lock();

    this->startedWorkers.store(0);

    this->closeRequests = AZG_NEW ConcurrentQueue<AsyncCloseReq>();
    this->openRequests = AZG_NEW ConcurrentQueue<AsyncOpenReq>();
    this->readRequests = AZG_NEW ConcurrentQueue<AsyncReadReq>();
    this->workers = AZG_NEW Thread*[AZGARD_FILE_SYSTEM_THREADS];

    io_lock.lock();

    for (size_t i = 0; i < AZGARD_FILE_SYSTEM_THREADS; i++) {
        workers[i] = AZG_NEW Thread(FileManager::workerRun, nullptr);
    }

    // Make shure that every worker have been started.

    io_lock.unlock();
    manager_lock.unlock();
}

void FileManager::shutDown() {
    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "File Manager Terminating...");
    delete FileManager::gInstancePtr;
    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "File Manager Terminated!");
}

FileManager::~FileManager() {
    this->shouldFileWorkersRun = false;
    this->waitPendingRequests();

    manager_lock.lock();

    for (size_t i = 0; i < AZGARD_FILE_SYSTEM_THREADS; i++) {
        workers[i]->join();
        delete workers[i];
    }

    delete this->workers;
    delete this->openRequests;
    delete this->closeRequests;
    delete this->readRequests;

    manager_lock.unlock();
}
void FileManager::waitPendingRequests() {
    manager_lock.lock();

    // Wait untial all requests have been served
    while(
           FileManager::openRequests->size()
        || FileManager::closeRequests->size()
        || FileManager::readRequests->size()
    ) {
        // When the job system kicks out we should probably use other strategy here
        Azgard::Thread::thisThread::yield();
    }
    manager_lock.unlock();

}

bool FileManager::haveRequests() {
    return this->openRequests->size()
            || this->closeRequests->size()
            || this->readRequests->size();
}

void FileManager::workerRun(void* data) {
    unsigned int old = 0;

    while(!FileManager::getSingletonPtr()) {
        Azgard::Thread::thisThread::yield();
    }
    FileManager* gManager = FileManager::getSingletonPtr();
    while (!gManager->startedWorkers.compareExchangeWeak(old, old+1)) {
        old = gManager->startedWorkers.load();
    }
 
    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "File worker %u started!", old);

    while(gManager->shouldFileWorkersRun) {
    
        if(gManager->shouldFileWorkersRun == false) break;

        while(!gManager->haveRequests() && gManager->shouldFileWorkersRun == true) {
            Azgard::Thread::thisThread::yield();
        }
 
        if(gManager->openRequests->size()) {
            // Handle Open File Request
            AsyncOpenReq req = gManager->openRequests->popFront();
            FileHandle& handle = req.handle;
            gManager->syncOpen(req.handle, req.path, req.mode);
            req.callback(req.handle);
        }
        
        if(gManager->readRequests->size()) {
            // Handle Read File Request
            AsyncReadReq req = gManager->readRequests->popFront();
            req.callback(req.file.syncRead(req.from, req.size));
        }
        

        if(gManager->closeRequests->size()) {
            // Handle Close File Request
            AsyncCloseReq req = gManager->closeRequests->popFront();
            gManager->syncClose(req.file);
            req.callback();
        }
    
    }

    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "File worker %u Ended!", old);
}

void FileManager::asyncOpen(FileHandle& handle, FileHandle::Path path, int fileMode, FileHandle::AsyncFileOpenCallback callback) {
    AsyncOpenReq req(handle);
    req.handle = handle;
    req.callback = callback;
    req.path = path;
    req.mode = fileMode;
    FileManager::openRequests->pushBack(req);
}

void FileManager::asyncColse(FileHandle& file, FileHandle::AsyncFileCloseCallback callback) {
    AsyncCloseReq req;
    req.callback = callback;
    req.file = file;
    FileManager::closeRequests->pushBack(req);
}