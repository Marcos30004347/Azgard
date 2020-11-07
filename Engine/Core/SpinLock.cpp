#include "SpinLock.hpp"

using namespace Azgard;

void SpinLock::lock() { while(_lock.exchange(1) == 1) {} }
void SpinLock::unlock() { _lock.exchange(0); }
