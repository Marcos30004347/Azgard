#include "Thread.hpp"
#include "Platform/Config.hpp"

#include <thread>

#if defined(LinuxPlatform) || defined(MacPlatform) || defined(IphonePlatform) 
#define PTHREADS 1
#include <pthread.h>
#elif defined(WindowsPlatform)
#define WINTHREADS 1
#include <winbase.h>
#elif defined(AndroidPlatform) 
#include <sched.h>
#endif


using namespace Azgard;

class Thread::NativeThreadHandle {
private:
    std::thread thread_;
    NativeThreadHandle(void (*fn)(void* data), void* data): thread_{fn, data} {}
    friend class Thread;
};

Thread::Thread(void (*fn)(void* data), void* data) {
    thread_handle_ = new NativeThreadHandle(fn, data);
}

Thread::~Thread() {
    this->thread_handle_->thread_.~thread();
    delete this->thread_handle_;
}

void Thread::join() noexcept {
    this->thread_handle_->thread_.join();
}

void Thread::close() noexcept { 
    this->~Thread();
}

void Thread::getId() noexcept {
    this->thread_handle_->thread_.get_id();
}

void Thread::swapWith(Thread& other) noexcept {
    this->thread_handle_->thread_.swap(other.thread_handle_->thread_);
}

unsigned int Thread::hardwareConcurrency() noexcept {
    return std::thread::hardware_concurrency();
}

bool Thread::thisThread::setAffinity(int core) {
    #if defined(PTHREADS)
    // pthread specific code
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core, &cpuset);

    pthread_t current_thread = pthread_self();
    int error = pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
    if(error) return false;
    return true;

    #elif defined(WINTHREADS)
    // WinThread specific code
    auto mask = (static_cast<DWORD_PTR>(1) << core);
    auto ret = SetThreadAffinityMask(_thread.native_handle(), mask);
    if(!ret) return false;
    return true;

    #elif defined(AndroidPlatform)
    cpu_set_t my_set;
    CPU_ZERO(&my_set);
    CPU_SET(7, &my_set);
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set);
    #endif
    return true;
}

void Thread::thisThread::yield() {
    std::this_thread::yield();
}
