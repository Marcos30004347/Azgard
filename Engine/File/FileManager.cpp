#include "Platform/Config.hpp"
#include "FileManager.hpp"

#include <string>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace Azgard;

char* replaceChar(const char* path, char a, char b) {
    unsigned int n = strlen(path);
    char* buff = new char[n + 1];
    for(int i=0; i<n; i++) {
        if(path[i] != a) buff[i] = path[i];
        else buff[i] = b;
    }
    buff[n] = '\0';
    return buff;
}


class FileManager::NativeFileHandle {
private:
    std::fstream fileStream_;

    friend FileManager;
};

FileManager* FileManager::open(const char* path, int fileMode) {
    NativeFileHandle* fileHandle = new NativeFileHandle();

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
    char* file_path = replaceChar(path, '/', '/');
    #endif

    fileHandle->fileStream_.open((const char*)file_path, (std::ios_base::openmode)mode);

    delete file_path;

    if(!fileHandle->fileStream_.is_open()) throw 10;


    FileManager* f = new FileManager();
    f->handle = fileHandle;

    return f;
}

void FileManager::close(FileManager* file) {
    delete file;
}

std::string FileManager::getBuffer() {
    std::stringstream stringStream;
    this->handle->fileStream_.seekg(0, std::ios::end);
    size_t size = this->handle->fileStream_.tellg();
    std::string buffer(size, ' ');
    this->handle->fileStream_.seekg(0);
    this->handle->fileStream_.read(&buffer[0], size); 

    return buffer.c_str();
}

std::string FileManager::getNextLine() {
    std::string line;
    getline( this->handle->fileStream_, line );
    return line;
}

bool FileManager::isEndOfFile() {
    return this->handle->fileStream_.eof();
}

void FileManager::write(std::string data) {
    if(this->handle->fileStream_.good())
        this->handle->fileStream_ << data;
}

FileManager::FileManager(): handle{nullptr} {}

FileManager::~FileManager() {
    this->handle->fileStream_.close();
}