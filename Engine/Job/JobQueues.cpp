#include "JobQueues.hpp"
#include "JobPriorityQueue.hpp"

using namespace Azgard;

jobPriorityQueue highPriorityQueue;
jobPriorityQueue mediumPriorityQueue;
jobPriorityQueue lowPriorityQueue;

JobQueues::JobQueues() {}

JobQueues::~JobQueues() {}

bool JobQueues::enqueue(Job* const &j) {
    if (j->priority == jobPriority::HIGH) return highPriorityQueue.enqueue(j);
    else if (j->priority == jobPriority::MEDIUM) return mediumPriorityQueue.enqueue(j);
    else return lowPriorityQueue.enqueue(j);
}

bool JobQueues::dequeue(Job* &j) {
    if (highPriorityQueue.dequeue(j)) return true;
    else if (mediumPriorityQueue.dequeue(j)) return true;
    else return lowPriorityQueue.dequeue(j);
}