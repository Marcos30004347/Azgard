#include "Platform/Config.hpp"

#include "PlatformManager.hpp"

namespace Azgard {

platform PlatformManager::getPlatform() noexcept {
    #if AZGARD_BROWSER_PLATFORM
    return platform::WebBrowser;
    #elif AZGARD_ANDROID_PLATFORM
    return platform::Android;
    #elif AZGARD_LINUX_PLATFORM
    return platform::Linux;
    #elif AZGARD_IOS_PLATFORM
    return platform::Ios;
    #elif AZGARD_MACOSX_PLATFORM
    return platform::Mac;
    #elif AZGARD_BROWSER_PLATFORM
    return platform::Windows;
    #endif
}

PlatformManager::PlatformManager() {}

PlatformManager::~PlatformManager() {}

}