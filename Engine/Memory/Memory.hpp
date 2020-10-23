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

