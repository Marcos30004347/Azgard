
#ifndef AZGARD_LIB_FILE_MANAGER
#define AZGARD_LIB_FILE_MANAGER

/**
 * TODO: When Job system kicks out will problably be more performant
 * to use it for async I/O operations.
 */

#include "Core/Engine.hpp"

#include "Core/ConcurrentQueue.hpp"
#include "Core/Thread.hpp"
#include "Core/SpinLock.hpp"
#include "Core/Singleton.hpp"

#include "Library/Name.hpp"
#include "Library/String.hpp"

#include "FileHandle.hpp"

namespace Azgard {

typedef void(*AsyncFileOpenCallback)(FileHandle& str);
typedef void(*AsyncFileCloseCallback)(void);




class AsyncOpenReq {
public:
    AsyncOpenReq(FileHandle& handle): handle{handle} {}
    FileHandle& handle;
    int mode = 0;
    FileHandle::Path path;
    AsyncFileOpenCallback callback;
};

class AsyncCloseReq {
public:
    FileHandle file;
    AsyncFileCloseCallback callback;
};


class FileManager: public Singleton<FileManager> {
public:
    void syncOpen(FileHandle& handle, FileHandle::Path path, int fileMode);
    void syncClose(FileHandle& file);

    void asyncOpen(FileHandle& handle, FileHandle::Path path, int fileMode, FileHandle::AsyncFileOpenCallback callback);
    void asyncColse(FileHandle& file, FileHandle::AsyncFileCloseCallback callback);

    static void startUp();
    static void shutDown();

private:
    FileManager();
    ~FileManager();

    Atomic<unsigned int> startedWorkers;
    SpinLock io_lock;
    SpinLock manager_lock;

    bool shouldFileWorkersRun;
    Thread** workers;

    static void workerRun(void* data);

    ConcurrentQueue<AsyncCloseReq>* closeRequests;
    ConcurrentQueue<AsyncOpenReq>* openRequests;
    ConcurrentQueue<AsyncReadReq>* readRequests;

    void waitPendingRequests();
    bool haveRequests();
    friend class FileHandle;
};


}
#endif