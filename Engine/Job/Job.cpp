#include "Job.hpp"

using namespace Azgard;

thread_local static Job* currentJob = nullptr;

Job* getCurrentJob() noexcept {
    return currentJob;
}

void setCurrentJob(Job* j) noexcept {
    currentJob = j;
}

void Job::execute(void* j) {
    Job* w = reinterpret_cast<Job*>(j);
    
    w->status = jobStatus::RUNNING;
    
    w->handler(w->promisePtr, w->resolverPtr);
    
    w->status = jobStatus::FINISHING;

    notifyCaller(w);
    returnToWorker();
}