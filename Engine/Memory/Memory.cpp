#include "Debug/Debugger.hpp"
#include "Debug/Logger.hpp"
#include "Memory.hpp"

#include <malloc.h>
#include <string.h>
#include <iostream>

#define STB_LEAKCHECK_IMPLEMENTATION
#include "stb_leakcheck.h"

void* Azgard::allocBytes(unsigned long size, const char* name, unsigned int line) {
    #ifdef AZGARD_DEBUG_BUILD
    void *ptr = stb_leakcheck_malloc(size, name, line);
    AZG_DEBUG_MALLOC(ptr, size)
    #else
    void *ptr = malloc(size);
    #endif
    return ptr;
}

void Azgard::dumpMemory() {
    #ifdef AZGARD_DEBUG_BUILD
    stb_leakcheck_dumpmem();
    #endif
}

void Azgard::freeBytes(void* ptr) {
    #ifdef AZGARD_DEBUG_BUILD
    stb_leakcheck_free(ptr);
    AZG_DEBUG_FREE(ptr)
    #else
    free(ptr);
    #endif
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
    return Azgard::allocBytes(size, __FILE__, __LINE__);
}

void* operator new(long unsigned int size, const char* filename, int line) {
    return Azgard::allocBytes(size, filename, line);
}

void* operator new[](long unsigned int size, const char* filename, int line) {
    return Azgard::allocBytes(size, filename, line);
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
