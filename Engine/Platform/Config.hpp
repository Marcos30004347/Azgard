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
#elif defined(__linux__) && !defined(__ANDROID__)
    #include"./Linux/Linux.hpp"
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE
    #include"./Iphone/Iphone.hpp"
    #elif TARGET_OS_MAC
    #include"./Mac/Mac.hpp"
    #elif
    #error "Unknown Apple Platform"
#endif
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include"./Windows/Windows.hpp"
#elif __unix__
    #include "./Unix/Unix.hpp"
#endif

#endif