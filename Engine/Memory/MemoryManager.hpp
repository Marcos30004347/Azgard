#ifndef AZGARD_MEMORY
#define AZGARD_MEMORY

#include "Memory.hpp"

/**
 * @brief New operator
 * 
 * @param size Size of memory to allocate.
 * @return voidless ptr to allocated memory.
 */
void* operator new(long unsigned int size) {
    return Azgard::allocBytes(size);
}

/**
 * @brief Celete operator
 * 
 * @param ptr ptr to delete
 */
void operator delete(void *ptr) noexcept {
    return Azgard::freeBytes(ptr);
}


#endif
