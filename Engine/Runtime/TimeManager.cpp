#include "TimeManager.hpp"
#include "Library/Thread.hpp"

#include <chrono>
#include <iostream>
#include <time.h>

using namespace std;
using namespace Azgard;

long TimeManager::programStart = 0;

void TimeManager::sleepFor(long long milli) {
   clock_t end_time;
   end_time = clock() + milli * CLOCKS_PER_SEC/1000;
   while (clock() < end_time) {

   }
}

long TimeManager::getMillisecondsSinseEpoch() noexcept {
   std::time_t result = std::time(nullptr);
   return result;
}

 Date TimeManager::getCurrentDate() {
   long milliseconds_sinse_epoch = TimeManager::getMillisecondsSinseEpoch();
   long milliseconds_remainder = milliseconds_sinse_epoch % 1000;
   tm* time = std::localtime(&milliseconds_sinse_epoch);

   Date date;
   date.day = time->tm_mday;
   date.month = time->tm_mon;
   date.year = time->tm_year + 1900;
   date.seconds = time->tm_sec;
   date.hour = time->tm_hour;
   date.minutes = time->tm_min;
   date.milliseconds = milliseconds_remainder;


   return date;
}

AZG_API long TimeManager::getProgramMilliseconds() noexcept {
   return getMillisecondsSinseEpoch() - TimeManager::programStart;
}

void TimeManager::startUp() {
   TimeManager::programStart = TimeManager::getMillisecondsSinseEpoch();
}

void TimeManager::shutDown() {}