#include "Debug/Debugger.hpp"
#include "Debug/Logger.hpp"
#include "Memory.hpp"

#include <malloc.h>
#include <string.h>
#include <iostream>

void* Azgard::allocBytes(unsigned long size) {
    void *ptr = malloc(size);
    AZG_DEBUG_MALLOC(ptr, size)
    return ptr;
}

void Azgard::freeBytes(void* ptr) {
    free(ptr);
    AZG_DEBUG_FREE(ptr)
}

void* Azgard::setBytesTo(void* ptr, int value, unsigned long count) {
    return memset(ptr, value, count);
}


void* Azgard::copyBytes(void* src, void* dest, unsigned int size) {
    return memcpy(dest, src, size);
}

/**
 * @brief New operator
 * 
 * @param size Size of memory to allocate.
 * @return voidless ptr to allocated memory.
 */
void* operator new(long unsigned int size) {
    // AZG_LOG(Azgard::LogChannel::CORE_CHANNEL, "allocado");
    return Azgard::allocBytes(size);
}

/**
 * @brief Celete operator
 * 
 * @param ptr ptr to delete
 */
void operator delete(void *ptr) noexcept {
    // AZG_LOG(Azgard::LogChannel::CORE_CHANNEL, "deallocado");
    return Azgard::freeBytes(ptr);
}
