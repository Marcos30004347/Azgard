#include "Core/TypeTraits.hpp"

namespace Azgard {

/**
 *  @brief  Forward an rvalue.
 *  @return The parameter cast to the specified type.
 *
 *  This function is used to implement "perfect forwarding".
 */
template<typename T>
constexpr T&& forward(typename removeReference<T>::type&& v) noexcept {
    static_assert(!isLeftValueReference<T>::value, "template argument" " substituting T is an lvalue reference type");
    return static_cast<T&&>(v);
}

/**
 *  @brief  Convert a value to an rvalue.
 *  @param  v  A thing of arbitrary type.
 *  @return The parameter cast to an rvalue-reference to allow moving it.
 */
template<typename T>
constexpr typename removeReference<T>::type&& move(T&& v) noexcept {
    return static_cast<typename removeReference<T>::type&&>(v);
}

}