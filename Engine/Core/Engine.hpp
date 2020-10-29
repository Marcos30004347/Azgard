#ifndef AZGARD_RUNTIME
#define AZGARD_RUNTIME

//Memory Stuff
#include "Memory/Memory.hpp"

// Assert
#include "Assert.hpp"

// Platform Stuff
#include "Platform/Config.hpp"

// Debug Stuff
#include "Debug/Debugger.hpp"
#include "Debug/Logger.hpp"

//Api stuff
#include "Core/Api.hpp"

//Type Traits stuff
#include "Core/TypeTraits.hpp"

//Move semantics stuff
#include "Core/Move.hpp"


#if defined(_MSC_VER)
struct construct { construct(void (*f)(void)) { f(); } };
#define constructor(fn) void fn(void); static constructor constructor_##fn(fn)
#define destructor(fn) void fn(void); static destructor destructor_##fn(fn)
#elif defined(__GNUC__) || defined(__CLANG__)
#define constructor(fn) void fn(void) __attribute__((constructor));
#define destructor(fn) void fn(void) __attribute__((destructor));
#endif


#endif