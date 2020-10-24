#ifndef AZGARD_MEMORY_MANAGER
#define AZGARD_MEMORY_MANAGER

#include "Core/Api.hpp"
#include "Memory.hpp"

namespace Azgard {
class MemoryManager {
public:
    AZG_API static void* mallocFromGlobalPool(long unsigned int size);
    AZG_API static void freeInGlobalPool(void* ptr);

    AZG_API static void startUpThreadLocalPool(); // Should be called in each initializing thread;
    AZG_API static void shutDownThreadLocalPool(); // Should be called in each terminating thread;

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
