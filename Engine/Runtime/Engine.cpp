#include "Runtime/Engine.hpp"

// Managers
#include "Memory/MemoryManager.hpp"
#include "Runtime/TimeManager.hpp"
#include "Event/EventManager.hpp"

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
    TimeManager::startUp();
    EventManager::startUp();
}

AZG_API void Azgard::Engine::shutDown() {
    // All Engine subsystems must be terminated at the right time
    // sinse some subsytems depend on each other. So do not change
    // the order of termination
 
    EventManager::shutDown();
    TimeManager::startUp();
    MemoryManager::shutDown();

    #ifdef AZGARD_DEBUG_BUILD
    Logger::shutDown();
    #endif
}