#ifndef AZGARD_RUNTIME
#define AZGARD_RUNTIME

//Memory Stuff
#include "Memory/Memory.hpp"
#include "Memory/MemoryManager.hpp"

// Assert
#include "Assert.hpp"

// Platform Stuff
#include "Platform/Config.hpp"

// Debug Stuff
#include "Debug/Debugger.hpp"
#include "Debug/Logger.hpp"

#if defined(AZGARD_WINDOWS_PLATFORM) && defined(AZGARD_SHARED_LIB_BUILD)
    #define AZGARGD_API __declspec(dllexport)
#elif defined(AZGARD_WINDOWS_PLATFORM) && defined(AZGARD_SHARED_LIB)
    #define AZGARGD_API __declspec(dllimport)
#elif defined(__GNUC__) && (defined(AZGARD_LINUX_PLATFORM) || defined(AZGARD_ANDROID_PLATFORM) || defined(AZGARD_IOS_PLATFORM) || defined(AZGARD_MACOSX_PLATFORM))
    #define AZGARGD_API __attribute__((visibility("default")))
#else
    #define AZGARGD_API
#endif

namespace Azgard {

template<typename T>
struct removeReference {
    typedef T   type;
};

/// IntegralConstant
template<typename T, T __v>
struct IntegralConstant
{
    static constexpr T                  value = __v;
    typedef T                           value_type;
    typedef IntegralConstant<T, __v>   type;
    constexpr operator value_type() const noexcept { return value; }
    #if __cplusplus > 201103L
    #define __cpp_lib_IntegralConstant_callable 201304
    constexpr value_type operator()() const noexcept { return value; }
    #endif
};

/// The type used as a compile-time boolean with false value.
typedef IntegralConstant<bool, false>    FalseType;
/// The type used as a compile-time boolean with true value.
typedef IntegralConstant<bool, true>     TrueType;

template<typename>
struct IslValueReference
: public FalseType { };

template<typename T>
struct IslValueReference<T&>
: public TrueType { };

template<typename>
struct IsRvalueReference
: public FalseType { };

template<typename T>
struct IsRvalueReference<T&&>
: public TrueType { };

/**
 *  @brief  Forward an rvalue.
 *  @return The parameter cast to the specified type.
 *
 *  This function is used to implement "perfect forwarding".
 */
template<typename T>
constexpr T&& forward(typename removeReference<T>::type&& v) noexcept {
    static_assert(!IslValueReference<T>::value, "template argument" " substituting T is an lvalue reference type");
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


void verifyAndLog(bool expression, const char* error_message) {
#ifdef AZG_DEBUG_BUILD
    if(expression) {
        AZGARD_LOG_ERROR(LogChannel::CORE_CHANNEL, error_message);
    }
#endif
}

}



#endif