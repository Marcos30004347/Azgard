#ifndef AZGARD_LIB_THREAD
#define AZGARD_LIB_THREAD

namespace Azgard {

class Thread {
private:
    class NativeThreadHandle;
    NativeThreadHandle* thread_handle_ = nullptr;

public:

    /**
     *   Return the number of hardware threads.
     */
    static unsigned int hardwareConcurrency() noexcept;

    Thread(void (*fn)(void* data), void* data);
    ~Thread();

    /**
     *   Wait thread to join.
     */
    void join() noexcept;

    /**
     *   Close running thread.
     */
    void close() noexcept;

    /**
     *   Returns thread id.
     */
    void getId() noexcept;

    /**
     *   Swap the state of a thread with the state of @other thread.
     */
    void swapWith(Thread& other) noexcept;


    class thisThread {
    public:
        /**
         * Set current running thread affinity to @core hardware core/thread.
         * @param core: hardware core/thread id to set affinity to.
         */
        static bool setAffinity(int core);

        /**
         * Yield's current thread execution, allowing another thread to run.
         */
        static void yield();
    };

};

}

#endif
