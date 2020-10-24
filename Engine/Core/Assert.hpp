#ifndef AZGARD_ASSERT
#define AZGARD_ASSERT

#include "Debug/Logger.hpp"
#include "Debug/Debugger.hpp"

namespace Azgard {

void abort();

#ifdef AZGARD_DEBUG_BUILD

#define AZG_CORE_ASSERT_AND_REPORT(exp, error_message, ...) \
    do { \
        if (!(exp)) { \
            AZG_LOG_ERROR(LogChannel::CORE_CHANNEL, error_message __VA_OPT__(,) __VA_ARGS__); \
            AZG_TRIGGER_BREAKPOINT; \
            abort(); \
        } \
    } while (false)


#define AZG_CORE_ASSERT(exp) \
    do { \
        if (!(exp)) { \
            AZG_TRIGGER_BREAKPOINT; \
            abort(); \
        } \
    } while (false)

}
#else

#define AZG_CORE_ASSERT_AND_REPORT(exp, error_message, ...)
#define AZG_CORE_ASSERT(exp)

}
#endif

#endif