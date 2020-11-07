#include "Runtime/Engine.hpp"

#ifdef AZGARD_DEBUG_BUILD
#include "Debug/Logger.hpp"
#endif

// Managers
#include "Memory/MemoryManager.hpp"
#include "Runtime/TimeManager.hpp"
#include "Event/EventManager.hpp"
#include "File/FileManager.hpp"
#include "Library/LibraryManager.hpp"

void Azgard::Engine::startUp() {
    AZG_DEBUG_SCOPE;
    // All Engine subsystems must be initialized at the right time
    // sinse some subsytems depend on each other. So do not change
    // the order of initialization
    #ifdef AZGARD_DEBUG_BUILD
    Logger::startUp();
    #endif

    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Engine Starting...");

    MemoryManager::startUp();
    LibraryManager::startUp();
    TimeManager::startUp();
    FileManager::startUp();

    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Engine Started");
    // EventManager::startUp();
}


void Azgard::Engine::shutDown() {
    // All Engine subsystems must be terminated at the right time
    // sinse some subsytems depend on each other. So do not change
    // the order of termination
 
    // EventManager::shutDown();
    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Engine Terminating...");

    FileManager::shutDown();
    TimeManager::shutDown();
    LibraryManager::shutDown();
    MemoryManager::shutDown();

    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Engine Terminated!");

    #ifdef AZGARD_DEBUG_BUILD
    Logger::shutDown();
    Azgard::dumpMemory();
    #endif
}


Azgard::Engine::Engine() { Azgard::Engine::startUp(); }
Azgard::Engine::~Engine() { Azgard::Engine::shutDown(); }