#include "Runtime/Engine.hpp"

// Managers
#include "Memory/MemoryManager.hpp"

#ifdef AZGARD_DEBUG_BUILD
#include "Debug/Logger.hpp"
#endif

AZG_API void Azgard::Engine::startUp() {
    // All Engine subsystems must be initialized at the right time
    // sinse some subsytems depend on each other. So do not change
    // the order of initialization

    #ifdef AZGARD_DEBUG_BUILD
    Logger::startUp();
    #endif

    MemoryManager::startUp();
}

AZG_API void Azgard::Engine::shutDown() {
    // All Engine subsystems must be terminated at the right time
    // sinse some subsytems depend on each other. So do not change
    // the order of termination
 
    MemoryManager::shutDown();

    #ifdef AZGARD_DEBUG_BUILD
    Logger::shutDown();
    #endif
}