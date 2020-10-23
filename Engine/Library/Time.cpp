#include "Time.hpp"
#include "Thread.hpp"

#include <time.h>

using namespace std;
using namespace Azgard;

void Time::sleepFor(unsigned int milli) {
   clock_t end_time;
   end_time = clock() + milli * CLOCKS_PER_SEC/1000;
   while (clock() < end_time) {

   }
}

