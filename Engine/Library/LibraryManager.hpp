#ifndef AZGARD_LIBRARY_MANAGER
#define AZGARD_LIBRARY_MANAGER

#include "Core/Engine.hpp"
#include "Singleton.hpp"

namespace Azgard {

class LibraryManager: public Singleton<LibraryManager> {
private:
    LibraryManager();
    ~LibraryManager();
public:
    static void startUp();
    static void shutDown();
};

}

#endif
