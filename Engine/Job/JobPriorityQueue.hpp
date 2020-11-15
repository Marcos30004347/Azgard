#ifndef JOBIN_WORK_QUEUES_LIST
#define JOBIN_WORK_QUEUES_LIST

#include "Core/ConcurrentRingBuffer.hpp"

namespace Azgard {

class Job;
using jobPriorityQueue = ConcurrentRingBuffer<Job*, 1024>;

}

#endif