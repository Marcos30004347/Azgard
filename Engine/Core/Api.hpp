/**
 * Azgard Api macros for shared libraries and static libraries 
 */

#if defined(AZGARD_WINDOWS_PLATFORM)
    #if defined(AZGARD_SHARED_LIB_BUILD)
    #define AZG_API __declspec(dllexport)
    #else 
    #define AZG_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__) && (defined(AZGARD_LINUX_PLATFORM) || defined(AZGARD_ANDROID_PLATFORM) || defined(AZGARD_IOS_PLATFORM) || defined(AZGARD_MACOSX_PLATFORM))
    #if defined(AZGARD_SHARED_LIB_BUILD)
    #define AZG_API __attribute__((visibility("default")))
    #else 
    #define AZG_API
    #endif
#else
    #define AZG_API
#endif