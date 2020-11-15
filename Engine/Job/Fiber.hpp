#ifndef JOBIN_FIBER_H
#define JOBIN_FIBER_H

#include "Core/Engine.hpp"
#include "Core/Atomic.hpp"

#ifdef FIBER_FCONTEXT_BACKEND
#include "fcontext/fcontext.h"
#elif FIBER_WINDOWS_BACKEND
#include <windows.h>
#include <malloc.h>
#elif FIBER_EMSCRIPTEN_BACKEND
#include <malloc.h>
#include <emscripten.h>
#include <emscripten/fiber.h>
#elif FIBER_CROSS_BACKEND
#include "cross-fiber/cross-fiber.hpp"


using cross_fiber = fiber_t;
#endif

namespace Azgard {

#ifdef FIBER_CROSS_BACKEND
static Atomic<fiber_t*> primary {nullptr};
#endif

class Fiber;

#ifdef FIBER_FCONTEXT_BACKEND
struct contextSwitchData {
    Fiber* to = nullptr;
    Fiber* from = nullptr;
    contextSwitchData(Fiber* _from, Fiber* _to): to {_to}, from {_from} {}
};
#endif

class Fiber {
private:
    void(*handle)(void*);
    void* args;

    #ifdef FIBER_FCONTEXT_BACKEND
    fcontext_t ctx;
    fcontext_stack_t stack =  { nullptr, 0 };
    friend void fiberEntry(fcontext_transfer_t caller);
    friend void fiberToThreadEntry(fcontext_transfer_t caller);
    #elif FIBER_WINDOWS_BACKEND
    void* stack;
    unsigned int stackSize;
    void* ctx;
    friend void fibHandle(void* fib);
    #elif FIBER_EMSCRIPTEN_BACKEND
    emscripten_fiber_t* ctx = nullptr;
    #elif FIBER_CROSS_BACKEND
    cross_fiber* ctx;
    #endif

    template<unsigned int size>
    friend class FiberPoolFixed;

    friend Fiber* createFiber();
    friend void initFiber(Fiber* fib, void(*handle)(void*), void* args);
    friend void convertThreadToFiber(Fiber* fib,  void(*handle)(void*), void* arg);
    friend void switchToFiber(Fiber* from, Fiber* to);
    friend void destroyFiber(Fiber* fib);
    friend void resetFiber(Fiber* fib, void(*handle)(void*), void* args);
    friend void createFiberStack(Fiber* fib, unsigned int stackSize);
    friend void destroyFiberStack(Fiber* fib);

    #ifdef FIBER_FCONTEXT_BACKEND
        Fiber(): ctx{nullptr}, stack{ nullptr,0 }, handle{ nullptr }, args{ 0 } {}
    #elif FIBER_WINDOWS_BACKEND
        Fiber(): ctx{nullptr}, stack{ nullptr }, handle{nullptr}, stack_size{0}, args{0} {}
    #elif FIBER_EMSCRIPTEN_BACKEND
        Fiber(): stack{ nullptr }, handle{nullptr}, stack_size{0}, args{0},  allocator{nullptr} {}
    #elif FIBER_CROSS_BACKEND
        Fiber(): ctx{nullptr}, handle{nullptr}, args{0}, allocator{nullptr} {}
    #endif

};

thread_local static Fiber* currentFiber = nullptr;

/**
 * Saves current context of @from and switch to @to context of execution.
 * @param from: fiber to save the context.
 * @param to: fiber to switch to.
 */

void switchToFiber(Fiber* from, Fiber* to);
void createFiberStack(Fiber* fib, unsigned int stackSize = 1024 * 60);
void destroyFiberStack(Fiber* fib);
void initFiber(Fiber* fib, void(*handle)(void*), void* args);

Fiber* createFiber();

void resetFiber(Fiber* fib, void(*handle)(void*), void* args);
void convertThreadToFiber(Fiber* fib, void(*handle)(void*), void* arg);
Fiber* getCurrentFiber();
void destroyFiber(Fiber* fib);

}

#endif