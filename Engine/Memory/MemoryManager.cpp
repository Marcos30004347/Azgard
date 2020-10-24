#include "Core/Assert.hpp"
#include "MemoryManager.hpp"
#include "MemoryPool.hpp"

using namespace Azgard;

thread_local MemoryPool* gMemoryPoll = nullptr;

void* MemoryManager::mallocFromGlobalPool(long unsigned int size) {
    AZG_CORE_ASSERT_AND_REPORT(gMemoryPoll != nullptr, "Memory manager not initialized!");
    return gMemoryPoll->alloc(size);
}

void MemoryManager::freeInGlobalPool(void* ptr) {
    AZG_CORE_ASSERT_AND_REPORT(ptr != nullptr, "Freeing null pointer!");
    AZG_CORE_ASSERT_AND_REPORT(gMemoryPoll != nullptr, "Memory manager not initialized!");

    return gMemoryPoll->free(ptr);
}

void MemoryManager::startUpThreadLocalPool() {
    gMemoryPoll = new MemoryPool();
 
}

void MemoryManager::shutDownThreadLocalPool() {
    delete gMemoryPoll;

}

void MemoryManager::startUp() {
    MemoryManager::startUpThreadLocalPool();
}

void MemoryManager::shutDown() {
    MemoryManager::shutDownThreadLocalPool();
}



