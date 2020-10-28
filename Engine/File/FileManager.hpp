
#ifndef AZGARD_LIB_FILE_MANAGER
#define AZGARD_LIB_FILE_MANAGER

/**
 * TODO: When Job system kicks out will problably be more performant
 * to use it for async I/O operations.
 */

#include "Core/Engine.hpp"

#include "Library/Concurrent/ConcurrentQueue.hpp"
#include "Library/Thread.hpp"
#include "Library/SpinLock.hpp"
#include "Library/Name.hpp"
#include "Library/String.hpp"

#include <fstream>

namespace Azgard {

typedef Name FilePath;

enum FileMode {
    binary = 1,
    atEnd = 2,
    read = 4,
    write = 8,
    truncate = 16,
    append = 32,
};


typedef void(*AsyncFileReadCallback)(String str);
typedef void(*AsyncFileOpenCallback)(FileHandle str);
typedef void(*AsyncFileCloseCallback)(void);

class FileHandle {
private:
    friend class FileManager;
    std::fstream* fileStream = nullptr;

public:
    void write(String data);
    String readEntireBuffer();
    String read(unsigned int size);

    void asyncReadEntireBuffer(AsyncFileReadCallback callback);
    void asyncRead(unsigned int size, AsyncFileReadCallback callback);
    bool isEndOfFile();

    FileHandle& operator=(FileHandle& other) {
        this->fileStream = other.fileStream;
        other.fileStream = nullptr;
    }
};


class AsyncReadEntireBurrerReq {
public:
    FileHandle file;
    AsyncFileReadCallback callback;
};

class AsyncReadReq {
public:
    unsigned int size;
    FileHandle file;
    AsyncFileReadCallback callback;
};

class AsyncOpenReq {
public:
    int mode = 0;
    FilePath path = "";
    AsyncFileOpenCallback callback;
};

class AsyncCloseReq {
public:
    FileHandle file;
    AsyncFileCloseCallback callback;
};



class FileManager {
public:
    static FileHandle open(FilePath path, int fileMode = FileMode::binary);
    static void close(FileHandle& file);

    static void asyncOpen(FilePath path, int fileMode, AsyncFileOpenCallback callback);
    static void asyncColse(FileHandle file, AsyncFileCloseCallback callback);

    static void startUp();
    static void shutDown();


    static void asyncOpen(AsyncFileOpenCallback callback);

private:
    static SpinLock io_lock;
    static SpinLock manager_lock;

    static bool shouldFileWorkersRun;
    static Thread** workers;

    static void workerRun(void* data);

    static ConcurrentQueue<AsyncCloseReq>* closeRequests;
    static ConcurrentQueue<AsyncOpenReq>* openRequests;
    static ConcurrentQueue<AsyncReadEntireBurrerReq>* readEntireBufferRequests;
    static ConcurrentQueue<AsyncReadReq>* readRequests;
    static void waitPendingRequests();

    friend class FileHandle;
};


}
#endif