#ifndef JOBIN_PROMISE_H
#define JOBIN_PROMISE_H

#include <tuple>
#include <type_traits>

extern void currentJobYield();
template <typename T> struct trait {
    typedef T type;
    T value = T();
    bool hasValidValue = true;

    trait() {}
    trait(T value): value {value} {}
    trait(trait<T>&& other): value {other.value} {}
};

template <> struct trait<void> {
    typedef void type;
    bool hasValidValue = false;

    trait() {}
    trait(trait<void>&& other) {}
};

template<typename T>
class Promise {
    template<typename Ret, typename... Args>

    friend class PromiseResolver;
    friend class JobManager;
    friend class Job;

    trait<T> promiseValue;

public:
    bool isResolved = false;
    
    Promise(): promiseValue{} {}

    bool hasValidReturn() {
        return promiseValue.hasValidValue;
    }

    template <typename Ret = T>
    typename std::enable_if<!std::is_void<Ret>::value>::type
    setValue(Ret&& v) {
        promiseValue.value = v;
    }

    inline void wait() noexcept {
        while(!this->isResolved) currentJobYield();
    }
};

#endif