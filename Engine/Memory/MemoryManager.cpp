#include "Core/Assert.hpp"
#include "MemoryManager.hpp"
#include "MemoryPool.hpp"

using namespace Azgard;

thread_local MemoryPool* gMemoryPoll = nullptr;

AZG_API void* MemoryManager::mallocFromGlobalPool(long unsigned int size) {
    AZG_CORE_ASSERT_AND_REPORT(gMemoryPoll != nullptr, "Memory manager not initialized!");
    return gMemoryPoll->alloc(size);
}

AZG_API void MemoryManager::freeInGlobalPool(void* ptr) {
    AZG_CORE_ASSERT_AND_REPORT(ptr != nullptr, "Freeing null pointer!");
    AZG_CORE_ASSERT_AND_REPORT(gMemoryPoll != nullptr, "Memory manager not initialized!");

    return gMemoryPoll->free(ptr);
}

AZG_API void MemoryManager::startUpThreadLocalPool() {
    gMemoryPoll = new MemoryPool();
 
}

AZG_API void MemoryManager::shutDownThreadLocalPool() {
    delete gMemoryPoll;

}

void MemoryManager::startUp() {
    MemoryManager::startUpThreadLocalPool();
}

void MemoryManager::shutDown() {
    MemoryManager::shutDownThreadLocalPool();
}



