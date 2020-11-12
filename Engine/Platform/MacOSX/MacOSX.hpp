/**
 * MacOsX configuration macros
 */
#define AZGARD_MACOSX_PLATFORM 1
#define SDL2Window 1

#define THREAD_PTHREAD_BACKEND
#define POSIX_PLATFORMv

#ifdef __x86_64__
  #define FIBER_FCONTEXT_BACKEND
#elif defined(i386) || defined(__i386) || defined(__i386__)
  #define FIBER_FCONTEXT_BACKEND 
#elif
  #error "Unknown OSX platform"
#endif
