#include "LibraryManager.hpp"
#include "Name.hpp"

using namespace Azgard;


LibraryManager::LibraryManager(){}
LibraryManager::~LibraryManager(){}


void LibraryManager::startUp() {
    AZG_DEBUG_SCOPE;
    LibraryManager::gInstancePtr = AZG_NEW LibraryManager();

    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "LibraryManager Starting...");
    Name::startUpNameHashTable();
    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "LibraryManager Started!");

}

void LibraryManager::shutDown() {
    AZG_DEBUG_SCOPE;
    delete LibraryManager::gInstancePtr;

    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "LibraryManager Terminating...");
    Name::shutDownNameHashTable();
    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "LibraryManager Terminated!");
}
