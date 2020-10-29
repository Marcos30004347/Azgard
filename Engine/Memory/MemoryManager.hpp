#ifndef AZGARD_MEMORY_MANAGER
#define AZGARD_MEMORY_MANAGER

#include "Memory.hpp"
#include "Library/Singleton.hpp"

namespace Azgard {
class MemoryManager: public Singleton<MemoryManager> {
    MemoryManager();
    ~MemoryManager();
public:
    void* mallocFromGlobalPool(long unsigned int size);
    void freeInGlobalPool(void* ptr);

    void startUpThreadLocalPool(); // Should be called in each initializing thread;
    void shutDownThreadLocalPool(); // Should be called in each terminating thread;

    static void startUp();
    static void shutDown();
};
}


#endif
