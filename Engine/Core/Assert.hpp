#ifndef AZGARD_ASSERT
#define AZGARD_ASSERT

#include "Debug/Logger.hpp"
#include "Debug/Debugger.hpp"

namespace Azgard {

void abort();

#define AZG_CORE_ASSERT_AND_REPORT(exp, error_message, ...) \
    do { \
        if (!(exp)) { \
            AZGARD_LOG_ERROR(LogChannel::CORE_CHANNEL, error_message __VA_OPT__(,) __VA_ARGS__); \
            abort(); \
        } \
    } while (false)


#define AZG_CORE_ASSERT(exp) \
    do { \
        if (!(exp)) { \
            abort(); \
        } \
    } while (false)


#define AZG_REPORT_ERROR_IF(exp, error_message, ...) \
    do { \
        if (!(exp)) { \
            AZGARD_LOG_ERROR(LogChannel::CORE_CHANNEL, error_message __VA_OPT__(,) __VA_ARGS__); \
        } \
        } while (false)
}

#endif