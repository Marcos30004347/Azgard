#ifndef AZGARD_FILE_HANDLE
#define AZGARD_FILE_HANDLE

#include "Core/Engine.hpp"
#include "Library/Name.hpp"
#include "Library/String.hpp"

#include <fstream>

namespace Azgard {


class FileStream {
private:
    unsigned int* references = nullptr;
    Name name;
    std::fstream* fileStream = nullptr;
public:

    FileStream();
    ~FileStream();

    FileStream& operator=(FileStream& other);

    inline bool isOpen() { return fileStream && fileStream->is_open(); }

    friend class FileHandle;
    friend class FileManager;
};

enum FileMode {
    binary = 1,
    atEnd = 2,
    read = 4,
    write = 8,
    truncate = 16,
    append = 32,
};

class FileHandle {
private:
    friend class FileManager;
    FileStream stream;
public:

    typedef Name Path;
    typedef void(*AsyncFileOpenCallback)(FileHandle& str);
    typedef void(*AsyncFileCloseCallback)(void);
    typedef void(*AsyncFileReadCallback)(String str);

    FileHandle();

    void syncOpen(Path path, int mode);
    void asyncOpen(Path path, int fileMode, AsyncFileOpenCallback callback);

    void syncClose();
    void asyncClose(AsyncFileCloseCallback callback);

    void syncWrite(String data);
    String syncRead(unsigned int from, unsigned int size);
    void asyncRead(unsigned int from, unsigned int size, AsyncFileReadCallback callback);
    bool isEndOfFile();
    unsigned int getFileSize();

    FileHandle& operator=(FileHandle& other);

    bool operator==(FileHandle& other) {
        return this->stream.fileStream == other.stream.fileStream;
    }

    inline bool isOpen() { return this->stream.isOpen(); }
};

class AsyncReadEntireBurrerReq {
public:
    FileHandle file;
    FileHandle::AsyncFileReadCallback callback;
};

class AsyncReadReq {
public:
    unsigned int from;
    unsigned int size;
    FileHandle file;
    FileHandle::AsyncFileReadCallback callback;
};


}

#endif
