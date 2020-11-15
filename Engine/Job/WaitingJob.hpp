#ifndef JOBIN_WAITING_JOB
#define JOBIN_WAITING_JOB

#include "Core/Atomic.hpp"

namespace Azgard {

class Job;

class WaitingJob {
public:
    Job* ref;
    Atomic<int> waitingFor;

    WaitingJob* next;
    WaitingJob* parent;

    WaitingJob(Job* j, int waitingFor): waitingFor{waitingFor}, ref{j} {}
    ~WaitingJob() {}
};

}

#endif