#include <stdlib.h>

#include "Fiber.hpp"

#ifdef FIBER_FCONTEXT_BACKEND

void fiberEntry(fcontext_transfer_t caller) {
    contextSwitchData* data = reinterpret_cast<contextSwitchData*>(caller.data);
    data->from->ctx = caller.ctx;

    void(*handle)(void*) = data->to->handle;
    void* args = data->to->args;
    delete data;
    handle(args);
}

void fiberToThreadEntry(fcontext_transfer_t caller) {
    Fiber* fib = reinterpret_cast<Fiber*>(caller.data);
    fib->ctx = caller.ctx;
    fib->handle(fib->args);

    jump_fcontext(caller.ctx, nullptr);
}

#elif FIBER_WINDOWS_BACKEND

void fibHandle(void* fib) {
    Fiber* f = reinterpret_cast<Fiber*>(fib);
    f->handle(f->args);
    exit(0);
}

#endif

/**
 * Saves current context of @from and switch to @to context of execution.
 * @param from: fiber to save the context.
 * @param to: fiber to switch to.
 */

void switchToFiber(Fiber* from, Fiber* to) {
    currentFiber = to;

    #ifdef FIBER_FCONTEXT_BACKEND
    contextSwitchData* data = AZG_NEW contextSwitchData(from, to);
    fcontext_transfer_t returner = jump_fcontext(to->ctx, data);
    data = reinterpret_cast<contextSwitchData*>(returner.data);
    data->from->ctx = returner.ctx;
    delete data;

    #elif FIBER_WINDOWS_BACKEND

    SwitchToFiber(to->ctx);

    #elif FIBER_EMSCRIPTEN_BACKEND

    emscripten_fiber_swap(from->ctx, to->ctx);

    #elif FIBER_CROSS_BACKEND

    fiber_switch(to->ctx);

    #endif
    currentFiber = from;
}

void createFiberStack(Fiber* fib, unsigned int stackSize) {
    
    #ifdef FIBER_FCONTEXT_BACKEND
    
    if(fib->stack.ssize) {
        destroy_fcontext_stack(&fib->stack);
    }

    fib->stack = create_fcontext_stack(stackSize);
    
    #elif FIBER_WINDOWS_BACKEND
    fib->stack = _malloca(stackSize);
    fib->stackSize = stackSize;
    
    #elif FIBER_EMSCRIPTEN_BACKEND
    void* stack = malloc(stackSize);
    void* astack = malloc(stackSize);
    fib->astack = astack;
    fib->stack = stack;
    fib->stackSize = stackSize;

    #elif FIBER_CROSS_BACKEND
    // Stack managed by the fiber api
    #endif
}

void destroyFiberStack(Fiber* fib) {
    #ifdef FIBER_FCONTEXT_BACKEND
    destroy_fcontext_stack(&fib->stack);
    #elif FIBER_WINDOWS_BACKEND
    delete fib->stack;
    #elif FIBER_EMSCRIPTEN_BACKEND
    delete fib->stack;
    delete fib->astack;
    #elif FIBER_CROSS_BACKEND
    // Stack managed by the fiber api
    #endif
}

void initFiber(Fiber* fib, void(*handle)(void*), void* args) {
    if (!currentFiber) abort();
    fib->args = args;
    fib->handle = handle;
    createFiberStack(fib);

    #ifdef FIBER_FCONTEXT_BACKEND
    fib->ctx = make_fcontext(fib->stack.sptr, fib->stack.ssize, fiberEntry);
     #elif FIBER_WINDOWS_BACKEND
    fib->ctx = CreateFiber(stack_s, stack, fib);
    #elif FIBER_EMSCRIPTEN_BACKEND
    emscripten_fiber_init(
        fib->ctx,
        fiber::callback,
        fib,
        stack,
        stack_s,
        astack,
        stack_s
    );
    #elif FIBER_CROSS_BACKEND
    fib->ctx = fiber_create(primary.load(), 1024*60, fib_handle, fib);
    #endif
}

Fiber* createFiber() {
    Fiber* fib = AZG_NEW Fiber();
    return fib;
}

void resetFiber(Fiber* fib, void(*handle)(void*), void* args) {
    if(!currentFiber) abort();
    
    #ifdef FIBER_FCONTEXT_BACKEND
    if(!fib->stack.ssize) createFiberStack(fib);
    fib->ctx = make_fcontext(fib->stack.sptr, fib->stack.ssize, fiberEntry);

    #elif FIBER_WINDOWS_BACKEND
    if(fib->ctx) { DeleteFiber(fib->ctx); }
    fib->ctx = CreateFiber(fib->stackSize, fib->stack, fib);
    
    #elif FIBER_EMSCRIPTEN_BACKEND
    emscripten_fiber_init(
        fib->ctx,
        fiber::callback,
        fib,
        fib->stack,
        fib->stackSize,
        fib->astack,
        fib->stackSize
    );
    #elif FIBER_CROSS_BACKEND
    if(fib->ctx) fiber_delete(fib->ctx);
    fib->ctx = fiber_create(primary.load(), 1024*60, fib_handle, fib);
    #endif

    fib->args = args;
    fib->handle = handle;
}

void convertThreadToFiber(Fiber* fib, void(*handle)(void*), void* arg) {
    fib->handle = handle;
    fib->args = arg;
    currentFiber = fib;

    createFiberStack(fib);

    #ifdef FIBER_FCONTEXT_BACKEND
    fib->ctx = make_fcontext(fib->stack.sptr, fib->stack.ssize, fiberToThreadEntry);
    fib->ctx = jump_fcontext(fib->ctx, fib).ctx;

    #elif FIBER_WINDOWS_BACKEND
    ConvertThreadToFiber(nullptr);
    fib->ctx = GetCurrentFiber();
    fib->handle(fib->args);
    ConvertFiberToThread();
    
    #elif FIBER_EMSCRIPTEN_BACKEND
    emscripten_fiber_init_from_current_context(
        fib->ctx,
        astack,
        stack_s
    );
    fib->handle(args);

    #elif FIBER_CROSS_BACKEND
    primary.compareExchangeStrong(nullptr, fiber_create(0, 0, 0, nullptr));
    fib = createFiber(init, args, fib_alocator);
    fib->allocator = &fib_alocator;
    fiber_switch(fib->ctx);
    
    #endif

    currentFiber = nullptr;

}

Fiber* getCurrentFiber() {
    return currentFiber;
}

void destroyFiber(Fiber* fib) {
    destroyFiberStack(fib);
    #ifdef FIBER_FCONTEXT_BACKEND
    delete fib;
    #elif FIBER_WINDOWS_BACKEND
    DeleteFiber(fib->ctx);
    #elif FIBER_EMSCRIPTEN_BACKEND
    delete fib->ctx;
    // delete fib;
    #elif FIBER_CROSS_BACKEND
    fiber_delete(fib->ctx);
    // delete fib;
    #endif
}

