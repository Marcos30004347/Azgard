#include "Debug/Debugger.hpp"
#include "Memory.hpp"

#include <malloc.h>
#include <string.h>

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
