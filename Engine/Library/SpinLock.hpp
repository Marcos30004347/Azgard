#ifndef AZGARD_SPIN_LOCK_H
#define AZGARD_SPIN_LOCK_H

#include "Atomic.hpp"

namespace Azgard {

class SpinLock {
    private:
    Atomic<int> _lock;

    public:
    SpinLock(): _lock{0} {}
    ~SpinLock() { _lock.~Atomic(); }
    void lock();
    void unlock();
};
}


#endif