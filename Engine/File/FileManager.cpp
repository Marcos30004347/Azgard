#include "Platform/Config.hpp"
#include "FileManager.hpp"

#include <sstream>

using namespace Azgard;

#ifndef AZGARD_FILE_SYSTEM_THREADS
#define AZGARD_FILE_SYSTEM_THREADS 3
#endif

Thread** FileManager::workers = nullptr;

SpinLock FileManager::io_lock;
SpinLock FileManager::manager_lock;

bool FileManager::shouldFileWorkersRun = true;

ConcurrentQueue<AsyncCloseReq>* FileManager::closeRequests = nullptr;
ConcurrentQueue<AsyncOpenReq>* FileManager::openRequests = nullptr;
ConcurrentQueue<AsyncReadEntireBurrerReq>* FileManager::readEntireBufferRequests = nullptr;
ConcurrentQueue<AsyncReadReq>* FileManager::readRequests = nullptr;


char* replaceChar(const char* path, char a, char b) {
    unsigned int n = Azgard::cStrLen(path);
    char* buff = new char[n + 1];
    for(int i=0; i<n; i++) {
        if(path[i] != a) buff[i] = path[i];
        else buff[i] = b;
    }
    buff[n] = '\0';
    return buff;
}


FileHandle FileManager::open(FilePath path, int fileMode) {
    AZG_DEBUG_SCOPE;
    FileHandle f = FileHandle();
    f.fileStream = new std::fstream();

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

    f.fileStream->open((const char*)file_path, (std::ios_base::openmode)mode);

    return f;
}

void FileManager::close(FileHandle& file) {
    AZG_DEBUG_SCOPE;

    if(file.fileStream) {
        file.fileStream->close();
        delete file.fileStream;
    }

    file.fileStream = nullptr;
}

String FileHandle::readEntireBuffer() {
    AZG_DEBUG_SCOPE;
    std::stringstream stringStream;
    fileStream->seekg(0, std::ios::end);
    size_t size = fileStream->tellg();
    std::string buffer(size, ' ');
    fileStream->seekg(0);
    fileStream->read(&buffer[0], size); 
    return String(buffer.c_str());
}

String FileHandle::read(unsigned int size) {
    AZG_DEBUG_SCOPE;
    std::string line;

    char* words = new char[size];

    fileStream->readsome(words, size);

    String result (words, size);

    delete words;

    return result;
}

bool FileHandle::isEndOfFile() {
    AZG_DEBUG_SCOPE;
    return fileStream->eof();
}

void FileHandle::write(String data) {
    AZG_DEBUG_SCOPE;
    if(fileStream->good())
        (*fileStream) << data.cString();
}

void FileHandle::asyncRead(unsigned int size, AsyncFileReadCallback callback) {
    AsyncReadReq req;
    req.file = *this;
    req.size = size;
    req.callback = callback;
    FileManager::readRequests->pushBack(req);
}


void FileHandle::asyncReadEntireBuffer(AsyncFileReadCallback callback) {
    AsyncReadEntireBurrerReq req;
    req.file = *this;
    req.callback = callback;
    FileManager::readEntireBufferRequests->pushBack(req);
}



void FileManager::startUp() {
    manager_lock.lock();

    FileManager::closeRequests = new ConcurrentQueue<AsyncCloseReq>();
    FileManager::openRequests = new ConcurrentQueue<AsyncOpenReq>();
    FileManager::readEntireBufferRequests = new ConcurrentQueue<AsyncReadEntireBurrerReq>();
    FileManager::readRequests = new ConcurrentQueue<AsyncReadReq>();

    FileManager::workers = new Thread*[AZGARD_FILE_SYSTEM_THREADS];

    io_lock.lock();

    for (size_t i = 0; i < AZGARD_FILE_SYSTEM_THREADS; i++) {
        workers[i] = new Thread(FileManager::workerRun, nullptr);
    }

    io_lock.unlock();
    manager_lock.unlock();

}

void FileManager::waitPendingRequests() {
    manager_lock.lock();
    // Wait untial all requests have been served
    while(
           FileManager::openRequests->size()
        || FileManager::closeRequests->size()
        || FileManager::readRequests->size()
        || FileManager::readEntireBufferRequests->size()
    ) {
        // When the job system kicks out we should probably use other strategy here
        Azgard::Thread::thisThread::yield();
    }
    manager_lock.unlock();

}

void FileManager::shutDown() {
    FileManager::waitPendingRequests();

    manager_lock.lock();

    for (size_t i = 0; i < AZGARD_FILE_SYSTEM_THREADS; i++) {
        workers[i]->join();
        delete workers[i];
    }

    delete FileManager::openRequests;
    delete FileManager::closeRequests;
    delete FileManager::readRequests;
    delete FileManager::readEntireBufferRequests;

    manager_lock.unlock();
}

void FileManager::workerRun(void* data) {
    while(FileManager::shouldFileWorkersRun) {
        if(FileManager::shouldFileWorkersRun == false) break;

        bool do_have_reqs = FileManager::openRequests->size()
        || FileManager::closeRequests->size()
        || FileManager::readRequests->size()
        || FileManager::readEntireBufferRequests->size();
    
        while((do_have_reqs == 0) && (FileManager::shouldFileWorkersRun == true)) {
            Azgard::Thread::thisThread::yield();
            do_have_reqs = FileManager::openRequests->size()
            || FileManager::closeRequests->size()
            || FileManager::readRequests->size()
            || FileManager::readEntireBufferRequests->size();
        }
 
        if(FileManager::openRequests->size()) {
            AsyncOpenReq req = FileManager::openRequests->popFront();
            req.callback(FileManager::open(req.path));
        } else if(FileManager::readRequests->size()) {
            AsyncReadReq req = FileManager::readRequests->popFront();
            req.callback(req.file.read(req.size));
        } else if(FileManager::readEntireBufferRequests->size()) {
            AsyncReadEntireBurrerReq req = FileManager::readEntireBufferRequests->popFront();
            req.callback(req.file.readEntireBuffer());
        } else if(FileManager::closeRequests->size()) {
            AsyncCloseReq req = FileManager::closeRequests->popFront();
            FileManager::close(req.file);
            req.callback();
        }
    }
}

void FileManager::asyncOpen(FilePath path, int fileMode, AsyncFileOpenCallback callback) {
    AsyncOpenReq req;
    req.callback = callback;
    req.path = path;
    req.mode = fileMode;
    FileManager::openRequests->pushBack(req);
}

void FileManager::asyncColse(FileHandle file, AsyncFileCloseCallback callback) {
    AsyncCloseReq req;
    req.callback = callback;
    req.file = file;
    FileManager::closeRequests->pushBack(req);
}