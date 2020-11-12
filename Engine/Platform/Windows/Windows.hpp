/**
 * Windows configuration macros
 */
#define AZGARD_WINDOWS_PLATFORM 1
#define SDL2Window 1

#define WINDOWS_PLATFORM
#define THREAD_WINDOWS_BACKEND
#define FIBER_WINDOWS_BACKEND

#ifdef __MINGW32__
#include <_mingw.h>
#ifdef __MINGW64_VERSION_MAJOR
#include <intrin.h>
#else
#include <mmintrin.h>
#endif
#else
#include <mmintrin.h>
#endif