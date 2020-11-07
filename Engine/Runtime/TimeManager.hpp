#ifndef AZGARD_LIB_TIME_MANGAER
#define AZGARD_LIB_TIME_MANGAER

#include "Core/Engine.hpp"
#include "Core/Singleton.hpp"

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

class TimeManager: public Singleton<TimeManager> {
    long programStart;

    TimeManager();
    ~TimeManager();
public:
    void sleepFor(long long ms);
    long getMillisecondsSinseEpoch() noexcept;
    long getProgramMilliseconds() noexcept;
    Date getCurrentDate();
    Date getDate(long milliseconds);

    static void startUp();
    static void shutDown();
};

}

#endif