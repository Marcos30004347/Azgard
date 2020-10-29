#ifndef AZGARD_MEMORY
#define AZGARD_MEMORY

namespace Azgard {

/**
 * @brief Allocate @cont bytes
 * 
 * @param cont The amount of bytes to allocate from the SO.
 * @return Pointer to the allocated memory.
 */
void* allocBytes(unsigned long size, const char* name, unsigned int line);


/**
 * @brief Give back to the operating system the @ptr memory
 * 
 * @param ptr The pointer to free.
 */
void freeBytes(void* ptr);

/**
 * @brief Copy @size from src to dest.
 * 
 * @param src Source to copy.
 * @param dest Destination of the copy.
 * @param size Number of copy copied.
 * @return Pointer to the copied memory.
 */
void* copyBytes(void* src, void* dest, unsigned int size);

/**
 * @brief Set @count bytes of @ptr to @value.  
 * 
 * @param ptr Pointer to memory to be set.
 * @param value Value to set memory with.
 * @param count The amount of bytes to set
 * @return Ptr to the reseted memory.
 */
void* setBytesTo(void* ptr, int value, unsigned long count);


/**
 * @brief Dumb Memory checking for leaks.
 */
void dumpMemory();


}
/**
 * @brief New operator
 * 
 * @param size Size of memory to allocate.
 * @return voidless ptr to allocated memory.
 */
void* operator new(long unsigned int size);

/**
 * @brief Debugged New operator
 * 
 * @param size Size of memory to allocate.
 * @return voidless ptr to allocated memory.
 */
void* operator new(long unsigned int size, const char* filename, int line);

void* operator new[](long unsigned int size, const char* filename, int line);


// void* operator new (long unsigned int size, const char* filename, int line);

// #define new(size) Azgard::allocBytes(size, __FILE__ , __LINE__)

/**
 * @brief Celete operator
 * 
 * @param ptr ptr to delete
 */
void operator delete(void *ptr) noexcept;

#ifdef AZGARD_DEBUG_BUILD
    #define AZG_NEW new (__FILE__ , __LINE__ )
#else
    #define AZG_NEW new
#endif


#endif
