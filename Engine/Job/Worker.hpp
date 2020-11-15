#ifndef JOBIN_WORKER_H
#define JOBIN_WORKER_H

#include "Job.hpp"
#include "Core/Thread.hpp"

namespace Azgard {

class Worker;

thread_local static Worker* currentWorker = nullptr;

class Worker {
    friend void returnToWorker();

private:
    /**
     * handler of the worker.
     */
    void(*handler)(void*);

    /**
     * voidless pointer to pass as argument to handler.
     */
    void* arg = nullptr;

    /**
     * thread of execution of this worker.
     */
    Thread* thread = nullptr;

    /**
     * flag that signal if workers can stop pooling jobs.
     */
    static bool shouldPool;

    /**
     * number of currently running workers.
     */
    static Atomic<unsigned int> runningWorkers;

    /**
     * worker id.
     */
    unsigned int id = 0;

    /**
     * Main routine of the worker, this function is responsable for
     * pooling and executing jobs.
     */
    static void doWork(void *data);

    /**
     * Routine responsable for setting up a worker for
     * the doWork method.
     */
    static void initWorker(void *data);

public:
    /**
     * Worker contructor.
     * @param handler: worker initial job;
     * @param arg: initial argument.
     */
    Worker(void(*handler)(void*), void* arg);

    /**
     * Worker contructor.
     * @note: this contrutor dont dispatch any initial job.
     */
    Worker();

    /**
     * wait for current worker to return.
     */
    void wait();

    /**
     * worker destructor.
     */
    ~Worker();

    /**
     * Convert current thread to a worker.
     */
    static void convertThreadToWorker(void(*handler)(void*), void* arg);

    class AllWorkers {
    public:
        /**
         * Let all workers end current executing jobs and exit
         */
        static void done();
        static void begin();
    };

};

}

#endif