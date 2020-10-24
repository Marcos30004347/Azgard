#include "Time.hpp"
#include "Thread.hpp"

#include <chrono>
#include <iostream>
#include <time.h>

using namespace std;
using namespace Azgard;

 void Time::sleepFor(long long milli) {
   clock_t end_time;
   end_time = clock() + milli * CLOCKS_PER_SEC/1000;
   while (clock() < end_time) {

   }
}

long Time::getMillisecondsSinseEpoch() noexcept {
   std::time_t result = std::time(nullptr);
   return result;
}

 Date Time::getDate(long milliseconds_sinse_epoch) {
   long long int milliseconds_remainder = milliseconds_sinse_epoch % 1000;
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
