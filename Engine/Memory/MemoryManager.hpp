#ifndef AZGARD_MEMORY_MANAGER
#define AZGARD_MEMORY_MANAGER

#include "Core/Api.hpp"
#include "Memory.hpp"

namespace Azgard {
class MemoryManager {
public:
    static void* mallocFromGlobalPool(long unsigned int size);
    static void freeInGlobalPool(void* ptr);

    static void startUpThreadLocalPool(); // Should be called in each initializing thread;
    static void shutDownThreadLocalPool(); // Should be called in each terminating thread;

    static void startUp();
    static void shutDown();
};
}


#define AZGARD_OVERLOAD_NEW \
void* operator new(long unsigned int size) { \
    return Azgard::MemoryManager::mallocFromGlobalPool(size); \
}

#define AZGARD_OVERLOAD_DELETE \
void operator delete(void* ptr) { \
    return Azgard::MemoryManager::freeInGlobalPool(ptr); \
}

#endif
