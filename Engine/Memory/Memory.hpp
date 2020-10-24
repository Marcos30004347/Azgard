#ifndef AZGARD_MEMORY
#define AZGARD_MEMORY

namespace Azgard {

/**
 * @brief Allocate @cont bytes
 * 
 * @param cont The amount of bytes to allocate from the SO.
 * @return Pointer to the allocated memory.
 */
void* allocBytes(unsigned long cont);

/**
 * @brief Give back to the operating system the @ptr memory
 * 
 * @param ptr The pointer to free.
 */
void freeBytes(void* ptr);


/**
 * @brief Set @count bytes of @ptr to @value.  
 * 
 * @param ptr Pointer to memory to be set.
 * @param value Value to set memory with.
 * @param count The amount of bytes to set
 * @return Ptr to the reseted memory.
 */
void* setBytesTo(void* ptr, int value, unsigned long count);

}

/**
 * @brief New operator
 * 
 * @param size Size of memory to allocate.
 * @return voidless ptr to allocated memory.
 */
void* operator new(long unsigned int size);

/**
 * @brief Celete operator
 * 
 * @param ptr ptr to delete
 */
void operator delete(void *ptr) noexcept;

#endif
