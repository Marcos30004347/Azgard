#ifndef AZGARD_LIB_PLATFORM

/**
 * @brief: Platform specific configuration macros.
 * 
 * Current platforms are:
 * 1. Browser
 * 2. Android
 * 3. Linux
 * 4. Mac
 * 5. Iphone
 * 6. Windows
 */

#if __EMSCRIPTEN__
#include"./Browser/Browser.hpp"
#elif __ANDROID__
#include"./Android/Android.hpp"
#elif __linux__
#include"./Linux/Linux.hpp"
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE
    #include"./Iphone/Iphone.hpp"
    #elif TARGET_OS_MAC
    #include"./Mac/Mac.hpp"
#endif
#elif __WIN32__
#include"./Windows/Windows.hpp"
#endif

#endif