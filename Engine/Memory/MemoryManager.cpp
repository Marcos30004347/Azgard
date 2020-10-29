#include "Core/Assert.hpp"
#include "MemoryManager.hpp"
#include "MemoryPool.hpp"

using namespace Azgard;

thread_local MemoryPool* gMemoryPoll = nullptr;

MemoryManager::MemoryManager() {}
MemoryManager::~MemoryManager() {}

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
    gMemoryPoll = AZG_NEW MemoryPool();
 
}

void MemoryManager::shutDownThreadLocalPool() {
    delete gMemoryPoll;

}

void MemoryManager::startUp() {
    AZG_DEBUG_SCOPE;
    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Memory Manager Starting...");

    MemoryManager::gInstancePtr = AZG_NEW MemoryManager();
    MemoryManager::gInstancePtr->startUpThreadLocalPool();

    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Memory Manager Started!");
}

void MemoryManager::shutDown() {
    AZG_DEBUG_SCOPE;
    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Memory Manager Terminating...");

    MemoryManager::gInstancePtr->shutDownThreadLocalPool();
    delete MemoryManager::gInstancePtr;

    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Memory Manager Terminated...");
}



