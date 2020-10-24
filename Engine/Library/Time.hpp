#ifndef AZGARD_LIB_TIMER
#define AZGARD_LIB_TIMER

#include "Core/Engine.hpp"

namespace Azgard {

struct Date {
    int day;
    int month;
    int year;
    int hour;
    int minutes;
    int seconds;
    long long milliseconds;
};

class Time {
public:
    AZG_API static void sleepFor(long long ms);
    AZG_API static long getMillisecondsSinseEpoch() noexcept;
    AZG_API static Date getDate(long milliseconds_sinse_epoch);
};

}

#endif