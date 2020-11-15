#ifndef JOBIN_MANAGER_H
#define JOBIN_MANAGER_H

#include <tuple>

#include "Job.hpp"
#include "JobQueues.hpp"
#include "WaitingJob.hpp"

namespace Azgard {

class JobManager {
    friend class Worker;
    friend void currentJobYield();
    friend void notifyCaller(Job* job);

    static JobQueues queues;

private:
    static WaitingJob* putToWait(Job* w, int waitingFor) {
        WaitingJob* waiting = AZG_NEW WaitingJob(w, waitingFor);
        return waiting;
    }

    static void notify(WaitingJob* ref) {
        int waiting;
        do {
            waiting = ref->waitingFor.load();
        } while (!ref->waitingFor.compareExchangeWeak(waiting, waiting - 1));

        if (waiting <= 1) {
            queues.enqueue(ref->ref);
            delete ref;
        }

    }

public:
    JobManager() = default;
    ~JobManager() = default;

    template<typename Ret, typename ...Args>
    static void enqueueJob(Promise<Ret>* p, Ret(*handle)(Args...), Args&&... args) {
        p->isResolved = false;
        Job* j = AZG_NEW Job(p, handle, std::forward<Args>(args)...);
        queues.enqueue(j);
    }

    // template<typename Ret, typename ...Args>
    // static void enqueueJobs(Promise<Ret>* promises, Ret(*handle)(Args...), std::tuple<Args...> args[], unsigned int count) {
    //     Job* j;

    //     for (int i=0; i<count; i++) {
    //         promises[i].isResolved = false;
    //         j = AZG_NEW Job(&promises[i], handle, args[i]);
    //         queues.enqueue(j);
    //     }
    // }

    // template<typename Ret, typename ...Args>
    // static void enqueueJobsAndWait(Promise<Ret>* promises, Ret(*handle)(Args...), std::tuple<Args...> args[], unsigned int count) {
    //     WaitingJob* ref = putToWait(getCurrentJob(), count);
    //     Job* j;

    //     for(int i=0; i<count; i++) {
    //         promises[i].isResolved = false;
    //         j = AZG_NEW Job(&promises[i], handle, args[i]);
    //         j->waitingForMe = ref;
    //         queues.enqueue(j);
    //     }

    //     returnToWorker();
    // }

    template<typename Ret, typename ...Args>
    static void enqueueJobAndWait(Promise<Ret>* p, Ret(*handle)(Args...), Args&&... args) {
        p->isResolved = false;
        WaitingJob* ref = putToWait(getCurrentJob(), 1);

        Job* j;

        j = AZG_NEW Job(p, handle, std::forward<Args>(args)...);
        j->waitingForMe = ref;

        queues.enqueue(j);
        returnToWorker();
    }


};









}

#endif