#include "TimeManager.hpp"
#include "Library/Thread.hpp"

#include <chrono>
#include <iostream>
#include <time.h>

using namespace std;
using namespace Azgard;

void TimeManager::sleepFor(long long milli) {
   AZG_DEBUG_SCOPE;
   clock_t end_time;
   end_time = clock() + milli * CLOCKS_PER_SEC/1000;
   while (clock() < end_time) {

   }
}

long TimeManager::getMillisecondsSinseEpoch() noexcept {
   AZG_DEBUG_SCOPE;
   std::time_t result = std::time(nullptr);
   return result;
}

Date TimeManager::getCurrentDate() {
   AZG_DEBUG_SCOPE;
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

Date TimeManager::getDate(long milliseconds) {
   AZG_DEBUG_SCOPE;
   long milliseconds_remainder = milliseconds % 1000;
   tm* time = std::localtime(&milliseconds);

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

long TimeManager::getProgramMilliseconds() noexcept {
   AZG_DEBUG_SCOPE;
   return getMillisecondsSinseEpoch() - TimeManager::programStart;
}

TimeManager::TimeManager() {
   this->programStart = TimeManager::getMillisecondsSinseEpoch();
}

TimeManager::~TimeManager() {}

void TimeManager::startUp() {
   AZG_DEBUG_SCOPE;

   AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Time Manager Starting...");
   TimeManager::gInstancePtr = AZG_NEW TimeManager();
   AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Time Manager Started!");
}

void TimeManager::shutDown() {
   AZG_DEBUG_SCOPE;

   AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Time Manager Terminating...");
   delete TimeManager::gInstancePtr;
   AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Time Manager Terminated!");
}