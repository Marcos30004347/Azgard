/**
 * Android configuration macros
 */
#define AZGARD_ANDROID_PLATFORM 1

// #define THREAD_PTHREAD_BACKEND
#define POSIX_PLATFORM

#ifdef __arm__   //ARM
    #define FIBER_FCONTEXT_BACKEND
#elif __aarch64__ //ARM64
    #define FIBER_FCONTEXT_BACKEND
#elif __x86_64__ //x86_64
    #define FIBER_FCONTEXT_BACKEND
#elif defined(__amd64) || defined(__amd64__) || defined(__x86_64)  // AMD64
    #define FIBER_FCONTEXT_BACKEND
#elif defined(i386) || defined(__i386) || defined(__i386__) //x86
    #define FIBER_FCONTEXT_BACKEND
#elif
    #error Unknown Android platform
#endif