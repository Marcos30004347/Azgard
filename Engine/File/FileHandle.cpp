#include "FileHandle.hpp"
#include "FileManager.hpp"

#include <sstream>

using namespace Azgard;


FileStream::FileStream() {
    if(!references) references = AZG_NEW unsigned int(1);
    else *references++;
}

FileStream& FileStream::operator=(FileStream& other) {
    delete this->references;

    this->references = other.references;
    this->fileStream = other.fileStream;
    *this->references += 1;
    return *this;
}

FileStream::~FileStream() {
    *references -= 1;
    if(references && *references == 0) {
        delete references;
        references = nullptr;
        AZG_CORE_ASSERT_AND_REPORT(!fileStream, "file: %s was not closed!", this->name.value());
    }
}

String FileHandle::syncRead(unsigned int from, unsigned int size) {
    AZG_DEBUG_SCOPE;
    AZG_CORE_ASSERT_AND_REPORT(this->isOpen(), "File %s not opened!", this->stream.name.value());

    char* words = AZG_NEW char[size];

    this->stream.fileStream->seekp(from);
    this->stream.fileStream->readsome(words, size);

    String result (words, size);

    delete words;
    return result;
}

bool FileHandle::isEndOfFile() {
    AZG_DEBUG_SCOPE;
    return this->stream.fileStream->eof();
}

void FileHandle::syncWrite(String data) {
    AZG_DEBUG_SCOPE;
    if(this->stream.fileStream->good())
        (*this->stream.fileStream) << data.cString();
}


void FileHandle::asyncRead(unsigned int from, unsigned int size, AsyncFileReadCallback callback) {
    AsyncReadReq req;
    req.from = from;
    req.file = *this;
    req.size = size;
    req.callback = callback;
    FileManager::getSingletonPtr()->readRequests->pushBack(req);
}




void FileHandle::syncOpen(Path path, int mode) {
    AZG_CORE_ASSERT_AND_REPORT(this->stream.fileStream == 0, "Cant open %s because FileHandle already have a valid stream!", path.value());
    // AZG_CORE_ASSERT_AND_REPORT(this->stream.fileStream == 0 && !this->stream.isOpen(), "FileHandle %s already open, close it before open/reopen %s!", this->stream.name.value(), path.value());

    stream.fileStream = AZG_NEW std::fstream();
    stream.name = path;
    FileManager::getSingletonPtr()->syncOpen(*this, path, mode);
}

void FileHandle::asyncOpen(Path path, int fileMode, AsyncFileOpenCallback callback){
    AZG_CORE_ASSERT_AND_REPORT(this->stream.fileStream == 0, "Cant open %s because FileHandle already have a valid stream!", path.value());

    stream.fileStream = AZG_NEW std::fstream();
    stream.name = path;

    FileManager::getSingletonPtr()->asyncOpen(*this, path, fileMode, callback);
}

FileHandle::FileHandle() {}


void FileHandle::syncClose() {
    FileManager::getSingletonPtr()->syncClose(*this);
}

void FileHandle::asyncClose(AsyncFileCloseCallback callback) {
    FileManager::getSingletonPtr()->asyncColse(*this, callback);
}
FileHandle& FileHandle::operator=(FileHandle& other) {
    this->stream = other.stream;
    return *this;
}

unsigned int FileHandle::getFileSize() {
    this->stream.fileStream->seekg(0, std::ios::end);
    unsigned int size = this->stream.fileStream->tellg();
    this->stream.fileStream->seekg(0, std::ios::beg);
    return size;
}
