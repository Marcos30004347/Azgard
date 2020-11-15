#ifndef JOBIN_WORK_H
#define JOBIN_WORK_H

#include "Library/String.hpp"
#include "Fiber.hpp"
#include "FiberPoolFixed.hpp"
#include "Core/SpinLock.hpp"
#include "PromiseResolver.hpp"
#include "WaitingJob.hpp"

namespace Azgard {

enum jobPriority {
    HIGH,
    MEDIUM,
    LOW
};

enum jobStatus {
    UNITIATED = 0,
    WAITING,
    RUNNING,
    FINISHING
};

class Job;

void returnToWorker();
void notifyCaller(Job* job);
void currentJobYield();
Job* getCurrentJob() noexcept;
void setCurrentJob(Job* j) noexcept;

using jobInvokeMethod = unsigned int (*)(void*, void*);

class Job {
    friend class Worker;
    friend class JobQueues;
    friend class JobManager;
    friend class JobWaitingList;
    friend class JobAvaliableQueue;

    friend void notifyCaller(Job* job);

    WaitingJob* waitingForMe = nullptr;
    Fiber* context = nullptr;
    FiberPoolFixed<256>* pool = nullptr;

    jobStatus status = UNITIATED;
    jobPriority priority = HIGH;

    jobInvokeMethod handler;
    SpinLock lock;

    void* resolverPtr = nullptr;
    void* promisePtr = nullptr;

    /**
     * Execute @j job.
     * @param j: job to execute.
     */
    static void execute(void* j);
    public:

    /**
     * job contructor.
     * @param promise: promise to assign to this job.
     * @param handle: job handle.
     * @param args: job arguments.
     */
    template<typename Ret, typename ...Args>
    Job(Promise<Ret>* promise, Ret(*handle)(Args...), Args&&... args): status{UNINITIATED}, priority{HIGH} {
       PromiseResolver<Ret, Args...>* resolver = AZG_NEW PromiseResolver<Ret, Args...>(handle, std::forward<Args>(args)...);
       resolverPtr = resolver;
       promisePtr = promise;
       handler = reinterpret_cast<jobInvokeMethod>(resolver->resolveWithResolver);
    }

      /**
     * job contructor.
     * @param promise: promise to assign to this job.
     * @param handle: job handle.
     * @param args: job arguments.
     */
    template<typename Ret, typename ...Args>
    Job(Promise<Ret>* promise, Ret(*handle)(Args...), std::tuple<Args...> args): status{UNINITIATED}, priority{HIGH} {
        PromiseResolver<Ret, Args...>* resolver = AZG_NEW PromiseResolver<Ret, Args...>(handle, std::forward<std::tuple<Args...>>(args));
        resolverPtr = resolver;
        promisePtr = promise;
        handler = reinterpret_cast<jobInvokeMethod>(resolver->resolveWithResolver);
    }

    Job() {}
    
    /**
     * job destructor.
     */
    ~Job() {
        delete (unsigned int*)resolverPtr;
    }


};

}

#endif