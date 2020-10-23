// #include <math.h>

#include "Core/Math.hpp"
#include "Core/Assert.hpp"
#include "Library/File.hpp"
#include "Memory/Memory.hpp"
#include "Memory/MemoryPool.hpp"

namespace Azgard {

// Value for freed memory 
static const int FREEED_MEMORY_CONTENT        = 0xAA;

// Initial Value for new allocated memory 
static const int NEW_ALLOCATED_MEMORY_CONTENT = 0xFF;


MemoryPool::MemoryPool(const unsigned int &sInitialMemoryPoolSize, const unsigned int &MemoryChunkSize, const unsigned int &sMinimalMemorySizeToAllocate, bool bSetMemoryData) {
  memory_chunk_size   = MemoryChunkSize;
  set_memory_data               = bSetMemoryData;
  minimal_memory_size_to_allocate = sMinimalMemorySizeToAllocate;

  allocateMemory(sInitialMemoryPoolSize);
}


MemoryPool::~MemoryPool() {
  freeAllAllocatedMemory();
  deallocateAllChunks();
  // Check for possible Memory-Leaks...
  AZG_CORE_ASSERT_AND_REPORT(object_count == 0, "Memory-Leak : You have not freed all allocated Memory");
}


void *MemoryPool::alloc(const unsigned int &sMemorySize) {
  unsigned int sBestMemBlockSize = calculateBestMemoryBlockSize(sMemorySize);  
  MemoryChunk *ptrChunk = nullptr;
  while(!ptrChunk) {
    // Is a Chunks available to hold the requested amount of Memory ?
    ptrChunk = findChunkSuitableToHoldMemory(sBestMemBlockSize);
    if(!ptrChunk) {
	  // No chunk can be found
	  // => Memory-Pool is to small. We have to request 
	  //    more Memory from the Operating-System....
	  sBestMemBlockSize = maxValue(sBestMemBlockSize, calculateBestMemoryBlockSize(minimal_memory_size_to_allocate));
      allocateMemory(sBestMemBlockSize);
    }
  }

  // Finally, a suitable Chunk was found.
  // Adjust the Values of the internal "TotalSize"/"UsedSize" Members and 
  // the Values of the MemoryChunk itself.
  used_memory_pool_size += sBestMemBlockSize;
  free_memory_pool_size -= sBestMemBlockSize;
  object_count++;
  setMemoryChunkValues(ptrChunk, sBestMemBlockSize);

  // eventually, return the Pointer to the User
  return ((void *) ptrChunk->Data);
}


void MemoryPool::free(void *ptrMemoryBlock, const unsigned int &sMemoryBlockSize) {
  // Search all Chunks for the one holding the "ptrMemoryBlock"-Pointer
  // ("MemoryChunk->Data == ptrMemoryBlock"). Eventually, free that Chunks,
  // so it beecomes available to the Memory-Pool again...
  MemoryChunk *ptrChunk = findChunkHoldingPointerTo(ptrMemoryBlock);
  if(ptrChunk) {
	  freeChunks(ptrChunk);
  }
  else {
	  AZG_CORE_ASSERT_AND_REPORT(false, "Requested Pointer not in Memory Pool");
  }
  AZG_CORE_ASSERT_AND_REPORT((object_count > 0), "Request to delete more Memory then allocated.");
  object_count--;
}

void MemoryPool::free(void *ptrMemoryBlock) {
  // Search all Chunks for the one holding the "ptrMemoryBlock"-Pointer
  // ("MemoryChunk->Data == ptrMemoryBlock"). Eventually, free that Chunks,
  // so it beecomes available to the Memory-Pool again...
  MemoryChunk *ptrChunk = findChunkHoldingPointerTo(ptrMemoryBlock);
  if(ptrChunk) {
	  freeChunks(ptrChunk);
  }
  else {
	  AZG_CORE_ASSERT_AND_REPORT(false, "Requested Pointer not in Memory Pool");
  }

  AZG_CORE_ASSERT_AND_REPORT(object_count > 0, "Request to delete more Memory then allocated.");

  object_count--;
}
bool MemoryPool::allocateMemory(const unsigned int &sMemorySize) {
  unsigned int neededChunks = calculateNeededChunks(sMemorySize);
  unsigned int sBestMemBlockSize = calculateBestMemoryBlockSize(sMemorySize);

  unsigned char *ptrNewMemBlock = (unsigned char *) Azgard::allocBytes(sBestMemBlockSize); // allocate from Operating System

  MemoryChunk *ptrNewChunks = (MemoryChunk *) Azgard::allocBytes((neededChunks * sizeof(MemoryChunk))); // allocate Chunk-Array to Manage the Memory
  AZG_CORE_ASSERT_AND_REPORT(((ptrNewMemBlock) && (ptrNewChunks)), "System ran out of Memory");

  total_memory_pool_size += sBestMemBlockSize;
  free_memory_pool_size += sBestMemBlockSize;
  memory_chunk_count += neededChunks;

  if(set_memory_data) {
    Azgard::setBytesTo(((void *) ptrNewMemBlock), NEW_ALLOCATED_MEMORY_CONTENT, sBestMemBlockSize);
  }

  return linkChunksToData(ptrNewChunks, neededChunks, ptrNewMemBlock);;
}


unsigned int MemoryPool::calculateNeededChunks(const unsigned int &sMemorySize) {
   float f = (float) (((float)sMemorySize) / ((float)memory_chunk_size));
   return ((unsigned int) Azgard::ceil(f));
}

unsigned int MemoryPool::calculateBestMemoryBlockSize(const unsigned int &sRequestedMemoryBlockSize) {
  unsigned int neededChunks = calculateNeededChunks(sRequestedMemoryBlockSize);
  return (neededChunks * memory_chunk_size);
}

void MemoryPool::freeChunks(MemoryChunk *ptrChunk) {
  // Make the Used Memory of the given Chunk available
  // to the Memory Pool again.

  MemoryChunk *ptrCurrentChunk = ptrChunk;
  unsigned int chunkCount = calculateNeededChunks(ptrCurrentChunk->UsedSize);
  for(unsigned int i = 0; i < chunkCount; i++) {
    if(ptrCurrentChunk) {
      // Step 1 : Set the allocated Memory to 'FREEED_MEMORY_CONTENT'
      // Note : This is fully Optional, but usefull for debugging
	  if(set_memory_data) {
        Azgard::setBytesTo(((void *) ptrCurrentChunk->Data), FREEED_MEMORY_CONTENT, memory_chunk_size);
	  }

    // Step 2 : Set the Used-Size to Zero
    ptrCurrentChunk->UsedSize = 0;

    // Step 3 : Adjust Memory-Pool Values and goto next Chunk
    used_memory_pool_size -= memory_chunk_size;
    ptrCurrentChunk = ptrCurrentChunk->Next;
	}
  }
}


MemoryChunk *MemoryPool::findChunkSuitableToHoldMemory(const unsigned int &sMemorySize)
{
  // Find a Chunk to hold *at least* "sMemorySize" Bytes.
  unsigned int chunksToSkip = 0;
  bool bContinueSearch = true;
  MemoryChunk *ptrChunk = ptr_cursor_chunk; // Start search at Cursor-Pos.
  for(unsigned int i = 0; i < memory_chunk_count; i++) {
    if(ptrChunk) {
      if(ptrChunk == ptr_last_chunk) {
          // End of List reached : Start over from the beginning 
          ptrChunk = ptr_first_chunk;
      }

      if(ptrChunk->DataSize >= sMemorySize) {
        if(ptrChunk->UsedSize == 0) {
          ptr_cursor_chunk = ptrChunk;
            return ptrChunk;
        }
      }
    
      chunksToSkip = calculateNeededChunks(ptrChunk->UsedSize);

	    if(chunksToSkip == 0) chunksToSkip = 1;
    
      ptrChunk = skipChunks(ptrChunk, chunksToSkip);
    } else {
      bContinueSearch = false;
    }
  }
  return nullptr;
}


MemoryChunk *MemoryPool::skipChunks(MemoryChunk *ptrStartChunk, unsigned int chunksToSkip)
{
	MemoryChunk *ptrCurrentChunk = ptrStartChunk;
	for(unsigned int i = 0; i < chunksToSkip; i++) {
		if(ptrCurrentChunk) {
		   ptrCurrentChunk = ptrCurrentChunk->Next;
		} else {
			// Will occur, if you try to Skip more Chunks than actually available
			// from your "ptrStartChunk" 
			AZG_CORE_ASSERT_AND_REPORT(false, "Chunk == nullptr was not expected.");
			break;
		}
	}
	return ptrCurrentChunk;
}


void MemoryPool::setMemoryChunkValues(MemoryChunk *ptrChunk, const unsigned int &sMemBlockSize)
{
  if((ptrChunk)) {
    // && (ptrChunk != ptr_last_chunk))
    ptrChunk->UsedSize = sMemBlockSize;
  } else {
	  AZG_CORE_ASSERT_AND_REPORT(false, "Invalid nullptr-Pointer passed");
  }
}


bool MemoryPool::writeMemoryDumpToFile(File* file) {
  bool bWriteSuccesfull = false;
  // std::ofstream ofOutputFile;
  // ofOutputFile.open(strFileName, std::ofstream::out | std::ofstream::binary);

  MemoryChunk *ptrCurrentChunk = ptr_first_chunk;
  while(ptrCurrentChunk) {
    // if(ofOutputFile.good()) {
		//   ofOutputFile.write(((char *)ptrCurrentChunk->Data), ((std::streamsize) memory_chunk_size));
    //   bWriteSuccesfull = true;
    // }
    file->write(((char *)ptrCurrentChunk->Data));
    ptrCurrentChunk = ptrCurrentChunk->Next;
  }
  // ofOutputFile.close();
  return bWriteSuccesfull;
}


bool MemoryPool::linkChunksToData(MemoryChunk *ptrNewChunks, unsigned int chunkCount, unsigned char *ptrNewMemBlock) {
  MemoryChunk *ptrNewChunk = nullptr;
  unsigned int memOffSet = 0;
  bool bAllocationChunkAssigned = false;
  for(unsigned int i = 0; i < chunkCount; i++) {
    if(!ptr_first_chunk) {
      ptr_first_chunk = setChunkDefaults(&(ptrNewChunks[0]));
      ptr_last_chunk = ptr_first_chunk;
      ptr_cursor_chunk = ptr_first_chunk;
    } else {
      ptrNewChunk = setChunkDefaults(&(ptrNewChunks[i]));
      ptr_last_chunk->Next = ptrNewChunk;
      ptr_last_chunk = ptrNewChunk;
    }
    
	  memOffSet = (i * ((unsigned int) memory_chunk_size));
    ptr_last_chunk->Data = &(ptrNewMemBlock[memOffSet]);

	// The first Chunk assigned to the new Memory-Block will be 
	// a "AllocationChunk". This means, this Chunks stores the
	// "original" Pointer to the MemBlock and is responsible for
	// "free()"ing the Memory later....
	if(!bAllocationChunkAssigned) {
		ptr_last_chunk->IsAllocationChunk = true;
		bAllocationChunkAssigned = true;
	}
  }
  return recalcChunkMemorySize(ptr_first_chunk, memory_chunk_count);
}


bool MemoryPool::recalcChunkMemorySize(MemoryChunk *ptrChunk, unsigned int chunkCount)
{
  unsigned int memOffSet = 0;
  for(unsigned int i = 0; i < chunkCount; i++) {
	  if(ptrChunk) {
	    memOffSet = (i * ((unsigned int) memory_chunk_size));
	    ptrChunk->DataSize = (((unsigned int) total_memory_pool_size) - memOffSet);
	    ptrChunk = ptrChunk->Next;
	  }
	  else {
		  AZG_CORE_ASSERT_AND_REPORT(false, "ptrChunk == nullptr");
      return false;
	  }
  }
  return true;
}


MemoryChunk *MemoryPool::setChunkDefaults(MemoryChunk *ptrChunk) {
  if(ptrChunk) {
    ptrChunk->Data = nullptr;
    ptrChunk->DataSize = 0;
    ptrChunk->UsedSize = 0;
	  ptrChunk->IsAllocationChunk = false;
    ptrChunk->Next = nullptr;
  }
  return ptrChunk;
}

MemoryChunk *MemoryPool::findChunkHoldingPointerTo(void *ptrMemoryBlock) {
	MemoryChunk *ptrTempChunk = ptr_first_chunk;
	while(ptrTempChunk) {
		if(ptrTempChunk->Data == ((unsigned char *) ptrMemoryBlock)) {
			break;
		}
		ptrTempChunk = ptrTempChunk->Next;
	}
	return ptrTempChunk;
}

void MemoryPool::freeAllAllocatedMemory() {
	MemoryChunk *ptrChunk = ptr_first_chunk;
	while(ptrChunk) {
		if(ptrChunk->IsAllocationChunk) {
			Azgard::freeBytes(((void *) (ptrChunk->Data)));
		}
		ptrChunk = ptrChunk->Next;
	}
}


void MemoryPool::deallocateAllChunks()
{
  MemoryChunk *ptrChunk = ptr_first_chunk;
  MemoryChunk *ptrChunkToDelete = nullptr;
  while(ptrChunk) {
    if(ptrChunk->IsAllocationChunk) {	
      if(ptrChunkToDelete) {
        Azgard::freeBytes(((void *) ptrChunkToDelete));
      }
      ptrChunkToDelete = ptrChunk;
    }
    ptrChunk = ptrChunk->Next;
  }
}

bool MemoryPool::isValidPointer(void *ptrPointer)
{
  MemoryChunk *ptrChunk = ptr_first_chunk;
	while(ptrChunk) {
		if(ptrChunk->Data == ((unsigned char *) ptrPointer)) {
			return true;
		}
		ptrChunk = ptrChunk->Next;
	}
	return false;
}

unsigned int MemoryPool::maxValue(const unsigned int &sValueA, const unsigned int &sValueB) const {
  if(sValueA > sValueB) {
	  return sValueA;
  }
  return sValueB;
}

}
