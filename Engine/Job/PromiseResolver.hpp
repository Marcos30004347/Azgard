#ifndef JOBIN_PROMISE_RESOLVER_H
#define JOBIN_PROMISE_RESOLVER_H

#include "Promise.hpp"

namespace Azgard {

/*
template params:
    Ret: return type
    Args: list of function argument types
*/

template<typename Ret, typename... Args>
class PromiseResolver {
private:
    std::tuple<Args...> arguments;
    Ret (*handle)(Args...);

    template<std::size_t... Is>
    inline Ret invoke(const std::tuple<Args...>&& tuple, std::index_sequence<Is...>) noexcept {
        return std::forward<Ret>(handle(std::get<Is>(tuple)...));
    }

public:
    PromiseResolver(Ret (*handle)(Args...), Args ...args) noexcept: handle{handle}, arguments{args...} {}
    PromiseResolver(Ret (*handle)(Args...), std::tuple<Args...>&& args) noexcept: handle{handle}, arguments{args} {}

    static void resolveWithResolver(Promise<Ret>* p, PromiseResolver<Ret, Args...>* inv) noexcept {
        p->setValue(std::forward<Ret>(inv->invoke(std::forward<std::tuple<Args...>>(inv->arguments), std::index_sequence_for<Args...>{})));
        p->isResolved = true;
    }
};

template<typename... Args>
class PromiseResolver<void, Args...> {
    friend class Job;

private:
    std::tuple<Args...> arguments;
    void(*handle)(Args...);

    template<std::size_t... Is>
    inline void invoke(const std::tuple<Args...>& tuple, std::index_sequence<Is...>) noexcept {
        handle(std::get<Is>(tuple)...);
    }

public:
    PromiseResolver(void(*handle)(Args...), Args... args) noexcept: handle{handle}, arguments{args...} {}
    PromiseResolver(void (*handle)(Args...), std::tuple<Args...>&& args) noexcept: handle{handle}, arguments{args} {}

    inline static void resolveWithResolver(Promise<void>* p, PromiseResolver<void, Args...>* inv) noexcept {
        inv->invoke(inv->arguments, std::index_sequence_for<Args...>{});
        p->isResolved = true;
    }
};

}

#endif