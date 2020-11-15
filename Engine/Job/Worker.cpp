#include "Worker.hpp"
#include "JobManager.hpp"
#include "FiberPoolFixed.hpp"

namespace Azgard {

bool Worker::shouldPool = false;

Atomic<unsigned int> Worker::runningWorkers{0};

/**
 * thread context of execution.
 */
thread_local Fiber* threadFib = nullptr;

/**
 * worker fiber pool.
 */
thread_local FiberPoolFixed<256> fiberPool;

void Worker::doWork(void *data) {
    Worker* me = reinterpret_cast<Worker*>(data);
    Promise<void> promiseH;
    Promise<void> promiseC;

    if (me->handler) {
        JobManager::enqueueJob<void, void*>(&promiseH, me->handler, std::move(me->arg));
    }

    do {
        me->id = Worker::runningWorkers.load();
    } while (!Worker::runningWorkers.compareExchangeWeak(me->id, me->id+1));

    // while(Worker::runningWorkers.load() < Thread::hardwareConcurrency());

    Thread::thisThread::setAffinity(me->id % Thread::hardwareConcurrency());

    Job* nextJob = nullptr;

    while(!shouldPool) {}

    while(Worker::shouldPool) {
        while(JobManager::queues.dequeue(nextJob)) {
            setCurrentJob(nextJob);
            if (getCurrentJob()->status == jobStatus::UNITIATED) {
                getCurrentJob()->pool = &fiberPool;
                getCurrentJob()->context = fiberPool.request();
                resetFiber(getCurrentJob()->context, Job::execute, getCurrentJob());
                getCurrentJob()->status = jobStatus::RUNNING;
            } else if (getCurrentJob()->status == jobStatus::WAITING) {
                getCurrentJob()->status = jobStatus::RUNNING;
            }

            getCurrentJob()->lock.lock();
            switchToFiber(threadFib, getCurrentJob()->context);

            getCurrentJob()->lock.unlock();
            if (getCurrentJob()->status == jobStatus::FINISHING) {
                getCurrentJob()->pool->release(getCurrentJob()->context);
                delete getCurrentJob();
            }
        }
    }

}

void Worker::initWorker(void *data) {
    Worker* me = reinterpret_cast<Worker*>(data);
    currentWorker = me;
    threadFib = createFiber();
    convertThreadToFiber(threadFib, Worker::doWork, data);
    destroyFiber(threadFib);
}

Worker::Worker(void(*handler)(void*), void* arg): arg{arg}, handler{handler}, thread{nullptr} {
    this->thread = AZG_NEW Thread(Worker::initWorker, this);
}

Worker::Worker(): arg{nullptr}, handler{nullptr}, thread{nullptr} {}

void Worker::wait() {
    Worker::runningWorkers.compareExchangeStrong(Worker::runningWorkers.load(), Worker::runningWorkers.load() - 1);
    thread->join();
    delete thread;
}

Worker::~Worker() {}

void Worker::convertThreadToWorker(void(*handler)(void*), void* arg) {
    Worker::AllWorkers::begin();
    Worker* me = AZG_NEW Worker;
    me->handler = handler;
    me->arg = arg;
    Worker::initWorker(me);
    delete me;
}

void Worker::AllWorkers::done() {
    Worker::shouldPool = false;
}

void Worker::AllWorkers::begin() {
    Worker::shouldPool = true;
}

void returnToWorker() {
    switchToFiber(getCurrentFiber(), threadFib);
}

void notifyCaller(Job* job) {
    if (job->waitingForMe) JobManager::notify(job->waitingForMe);
}

void currentJobYield() {
    JobManager::queues.enqueue(getCurrentJob());
    returnToWorker();
}

}