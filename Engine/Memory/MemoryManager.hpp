#ifndef AZGARD_MEMORY_MANAGER
#define AZGARD_MEMORY_MANAGER

#include "Core/Api.hpp"
#include "Memory.hpp"

class MemoryManager {
public:
    AZG_API static void* mallocFromGlobalPool(long unsigned int size);
    AZG_API static void freeInGlobalPool(void* ptr);

    AZG_API static void startUp();
    AZG_API static void shutDown();
};


#define AZGARD_OVERLOAD_NEW \
void* operator new(long unsigned int size) { \
    return MemoryManager::mallocFromGlobalPool(size); \
}

#define AZGARD_OVERLOAD_DELETE \
void operator new(void* ptr) { \
    return MemoryManager::freeInGlobalPool(ptr); \
}


#endif
