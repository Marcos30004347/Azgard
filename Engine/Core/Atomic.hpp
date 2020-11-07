#ifndef AZGARD_LIB_ATOMIC
#define AZGARD_LIB_ATOMIC

#include <atomic>

namespace Azgard {

template <typename T>
class Atomic {
private:
    std::atomic<T> _atomic;

public:
    Atomic(T initial): _atomic{initial} {}

    Atomic(): _atomic{} {}

    ~Atomic() {}

    bool compareExchangeStrong(T current_value, T new_value){
        return _atomic.compare_exchange_strong(current_value, new_value);
    }

    bool compareExchangeWeak(T current_value, T new_value) {
        return _atomic.compare_exchange_weak(current_value, new_value);
    }

    T exchange(T value) {
        return _atomic.exchange(value);
    }

    T load() {
        return _atomic.load();
    }

    void store(T value) {
        _atomic.store(value);
    }
};

}

#endif