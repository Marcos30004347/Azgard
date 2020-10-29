// Code modified from https://www.codeproject.com/Articles/15527/C-Memory-Pool]

#ifndef AZGARD_MEMORY_POOL
#define AZGARD_MEMORY_POOL

#include "File/FileHandle.hpp"


namespace Azgard {

/**
 * @brief Interface Class (pure Virtual) for the MemoryPool.
 */
class MemoryPoolInterface
{
  public :
    virtual ~MemoryPoolInterface() {};

    virtual void *alloc(const unsigned int &sMemorySize) = 0;
    virtual void free(void *ptrMemoryBlock) = 0;
};

/**
 * @brief This struct will hold (and manage) the actual allocated Memory.
 */
struct MemoryChunk
{
	//The actual Data
	unsigned char *Data;

	//Size of the "Data"-Block
	unsigned int DataSize;

	//actual used Size
	unsigned int UsedSize;

	//true, when this MemoryChunks Points to a "Data"-Block which can be deallocated via "free()"
	bool IsAllocationChunk;

	//Pointer to the Next MemoryChunk in the List (may be NULL)
	MemoryChunk *Next;
};


class MemoryPool : public MemoryPoolInterface {
private :
    MemoryChunk *ptr_first_chunk = nullptr;
    MemoryChunk *ptr_last_chunk = nullptr;
    MemoryChunk *ptr_cursor_chunk = nullptr;

    unsigned int total_memory_pool_size = 0;
    unsigned int used_memory_pool_size = 0;
    unsigned int free_memory_pool_size = 0;
    unsigned int memory_chunk_count = 0;
	unsigned int object_count = 0;

	bool set_memory_data;

    unsigned int memory_chunk_size;
	unsigned int minimal_memory_size_to_allocate;

	/**
	 * @brief Alocate @sMemorySize from SO.
	 * 
	 * @param sMemorySize The amount
	 * @return true 
	 */
    bool allocateMemory(const unsigned int &sMemorySize);

	/**
	 * @brief Will free all Aloocated Memory to the Operating-System again.
	 * 
	 */
	void freeAllAllocatedMemory();

	/**
	 * @brief Calculates the number of MemoryChunks needed to Manage "sMemorySize" Bytes.
	 * 
	 * @param sMemorySize The amount of memory to check
	 * @return the Number of MemoryChunks needed to Manage "sMemorySize" Bytes.
	 */
    unsigned int calculateNeededChunks(const unsigned int &sMemorySize);


	/**
	 * @brief 
	 * 
	 * @param sRequestedMemoryBlockSize 
	 * @return the amount of Memory which is best Managed by the MemoryChunks.
	 */
    unsigned int calculateBestMemoryBlockSize(const unsigned int &sRequestedMemoryBlockSize);


	/**
	 * @brief Return a Chunk that can hold @sMemorySize amount of memory
	 * 
	 * @param sMemorySize - The amount of memory needed. 
	 * @return the Chunk which can hold the requested amount of memory, or NULL, if none was found.
	 */
    MemoryChunk *findChunkSuitableToHoldMemory(const unsigned int &sMemorySize);

	/**
	 * @brief Return the chunk holding the @ptrMemoryBlock ptr.
	 * 
	 * @param ptrMemoryBlock ptr to find
	 * @return Find a Chunk which "Data"-Member is Pointing to the given "ptrMemoryBlock", or NULL if none was found.
	 */
    MemoryChunk *findChunkHoldingPointerTo(void *ptrMemoryBlock);

	/**
	 * @brief Skip the given amount of Chunks, starting from the given ptrStartChunk.
	 * 
	 * @param ptrStartChunk Chunk to start skipping.
	 * @param chunksToSkip Number of Chunks to skip.
	 * @return the Chunk at the "skipping"-Position.
	 */
	MemoryChunk *skipChunks(MemoryChunk *ptrStartChunk, unsigned int chunksToSkip);

	/**
	 * @brief Set "Default"-Values to the given Chunk
	 * 
	 * @param ptrChunk Chunk to work with.
	 * @return updated chunks
	 */
    MemoryChunk *setChunkDefaults(MemoryChunk *ptrChunk);

	/**
	 * @brief Makes the memory linked to the given Chunk available in the MemoryPool again.
	 * 
	 * @param ptrChunk - Chunk to free.
	 */
    void freeChunks(MemoryChunk *ptrChunk);

	/**
	 * @brief Deallocates all Memory needed by the Chunks back to the Operating-System.
	 */
	void deallocateAllChunks();

	/**
	 * @brief Link the given Memory-Block to the Linked-List of MemoryChunks...
	 * 
	 * @param ptrNewChunk 
	 * @param chunkCount 
	 * @param ptrNewMemBlock 
	 * @return true 
	 */
    bool linkChunksToData(MemoryChunk *ptrNewChunk, unsigned int chunkCount, unsigned char *ptrNewMemBlock); //!< Link the given Memory-Block to the Linked-List of MemoryChunks...

	/**
	 * @brief Set the "UsedSize"-Member of the given "ptrChunk" to "sMemBlockSize".
	 * 
	 * @param ptrChunk 
	 * @param sMemBlockSize 
	 */
	void setMemoryChunkValues(MemoryChunk *ptrChunk, const unsigned int &sMemBlockSize);

	/**
	 * @brief Recalcs the "DataSize"-Member of all Chunks whe the Memory-Pool grows (via "AllocateMemory()")
	 * 
	 * @param ptrChunks 
	 * @param uiChunkCount 
	 * @return true 
	 * @return false 
	 */
	bool recalcChunkMemorySize(MemoryChunk *ptrChunks, unsigned int uiChunkCount);


	/**
	 * @brief Calculate max vamlue between a and b.
	 * 
	 * @param a 
	 * @param b 
	 * @return the greatest of the two input values (A or B) 
	 */
	unsigned int maxValue(const unsigned int &a, const unsigned int &b) const;
	

public :

	/**
	 * @brief Construct a new Memory Pool object
	 * 
	 * @param sInitialMemoryPoolSize The Initial Size (in Bytes) of the Memory Pool
	 * @param MemoryChunkSize The Size (in Bytes) each MemoryChunk can Manage. 
	 * @param sMinimalMemorySizeToAllocate sMinimalMemorySizeToAllocate The Minimal amount of Memory which is allocated (in Bytes).
	 * That means, every time you have to allocate more Memory from the Operating-System, at least sMinimalMemorySizeToAllocate Bytes are allocated.
	 * When you have to request small amount of Memory very often, this will speed up the MemoryPool,
	 * beacause when you allocate a new Memory from the OS, you will allocate a small "Buffer" automatically,
	 * wich will prevent you from requesting OS-memory too often.
	 * @param bSetMemoryData Set to true, if you want to set all allocated/freed Memory to a specific Value. Very usefull for debugging, but has a negativ impact on the runtime.
	 */
    MemoryPool(const unsigned int &sInitialMemoryPoolSize = 1000,  const unsigned int &MemoryChunkSize = 128, const unsigned int &sMinimalMemorySizeToAllocate = 2000, bool bSetMemoryData = false);

	/**
	 * @brief Destroy the Memory Pool object.
	 */
    virtual ~MemoryPool(); //!< Destructor

	/**
	 * @brief Get the Memory object
	 * 
	 * @param sMemorySize Sizes (in Bytes) of Memory.
	 * @return Pointer to a Memory-Block of "sMemorySize" Bytes, or NULL if an error occured. 
	 */
    virtual void *alloc(const unsigned int &sMemorySize);

	/**
	 * @brief Free the allocated memory again....
	 * 
	 * @param ptrMemoryBlock Pointer to a Block of Memory, which is to be freed (previoulsy allocated via "alloc()").
	 */
	virtual void free(void *ptrMemoryBlock);


	/**
	 * @brief  Writes the contents of the MemoryPool to a File. This file can be quite large (several MB).
	 * 
	 * @param file File of the MemoryDump.
	 * @return true on success, false otherwise  
	 */
    bool writeMemoryDumpToFile(FileHandle file);

	/**
	 * @brief Check, if a Pointer is in the Memory-Pool. Remainder that this Checks only if a pointer is inside the Memory-Pool,
	 * and <b>not</b> if the Memory contains meaningfull data.
	 * 
	 * @param ptrPointer Pointer to a Memory-Block which is to be checked.
	 * @return true, if the Pointer could be found in the Memory-Pool, false otherwise. 
	 */
	bool isValidPointer(void *ptrPointer);

};

}

#endif
