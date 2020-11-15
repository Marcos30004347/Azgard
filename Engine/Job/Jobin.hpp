#ifndef JOBIN_SYSTEM_H
#define JOBIN_SYSTEM_H

#include <iostream>
#include "Worker.hpp"
#include "JobManager.hpp"

namespace Azgard {

namespace Jobin {

namespace {
    Worker** workers = nullptr;
    unsigned int workersCount = 0;
};

template<typename T, typename ...Args>
static void async(Promise<T>* p, T(*handle)(Args...) ,Args&&... args) {
    return JobManager::enqueueJob<T, Args...>(p, handle, std::forward<Args>(args)...);
}

template<typename T, typename ...Args>
static void sync(Promise<T>* p, T(*handle)(Args...), Args&&... args) {
    return JobManager::enqueueJobAndWait(p, handle, std::forward<Args>(args)...);
}

static void done() {
    Worker::AllWorkers::done();
}

static void init(void(*handler)(void* data), void* data) {
    workersCount = Thread::hardwareConcurrency();
    workers = (Worker**)malloc(sizeof(Worker*)*workersCount - 1);

    for (int i=0; i<workersCount - 1; i++) {
        workers[i] = AZG_NEW Worker();
    }

    Worker::convertThreadToWorker(handler, data);
}

static void waitJobs() {
    for (int i=0; i<workersCount; i++) {
        workers[i]->wait();
    }
}

static void shutDown() {
    for (int i=0; i<workersCount - 1; i++) {
        delete workers[i];
    }
}

};

};

#endif