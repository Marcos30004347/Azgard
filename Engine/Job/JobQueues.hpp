#ifndef JOBIN_JOB_QUEUES_H
#define JOBIN_JOB_QUEUES_H

#include "Job.hpp"

namespace Azgard {

class JobQueues {
    public:

    JobQueues();
    ~JobQueues();
    bool enqueue(Job* const &j);
    bool dequeue(Job* &j);
    };


}

#endif