#ifndef AZGARD_PLATFORM_MANAGER
#define AZGARD_PLATFORM_MANAGER

#include "Library/Singleton.hpp"

using namespace Azgard;

namespace Azgard {

enum platform {
    Android = 0,
    Iphone,
    Windows,
    Mac,
    Linux,
    WebBrowser
};

class PlatformManager: public Singleton<PlatformManager> {
public:

    void startUp();
    void shutDown();

    platform getPlatform() noexcept;
    PlatformManager();
    ~PlatformManager();
private:
    static PlatformManager* singleton_ptr;
};

}


#endif