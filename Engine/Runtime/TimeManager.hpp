#ifndef AZGARD_LIB_TIME_MANGAER
#define AZGARD_LIB_TIME_MANGAER

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

class TimeManager {
    static long programStart;
public:
    AZG_API static void sleepFor(long long ms);
    AZG_API static long getMillisecondsSinseEpoch() noexcept;
    AZG_API static long getProgramMilliseconds() noexcept;
    AZG_API static Date getCurrentDate();

    static void startUp();
    static void shutDown();
};

}

#endif