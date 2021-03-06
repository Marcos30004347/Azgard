#ifndef JOBIN_RING_BUFFER_H
#define JOBIN_RING_BUFFER_H

#include "SpinLock.hpp"

namespace Azgard {

template<typename T, unsigned int ring_size>
class ConcurrentRingBuffer {
    T buff[ring_size];
    SpinLock mutex;

    unsigned int top = 0, tail = 0, _size = 0;

    public:

    ConcurrentRingBuffer();
    ~ConcurrentRingBuffer();
    bool enqueue(const T& data);
    bool dequeue(T& value);

    unsigned int size() { return _size; }
};

template<typename T, unsigned int ring_size>
ConcurrentRingBuffer<T,ring_size>::ConcurrentRingBuffer(): mutex{}, top{0}, tail{0}, _size{0} {}

template<typename T, unsigned int ring_size>
ConcurrentRingBuffer<T,ring_size>::~ConcurrentRingBuffer() {}

template<typename T, unsigned int ring_size>
bool ConcurrentRingBuffer<T,ring_size>::enqueue(const T& data) {
    mutex.lock();
    if((top + 1)%(ring_size+1) == tail) {
        mutex.unlock();
        return false;
    }
    _size++;
    buff[top] = data;

    top = (top + 1)%(ring_size+1);

    mutex.unlock();
    return true;
}


template<typename T, unsigned int ring_size>
bool ConcurrentRingBuffer<T, ring_size>::dequeue(T& value) {
    mutex.lock();
    if(top == tail) {
        mutex.unlock();
        return false;
    }
    _size--;

    value = buff[tail];
    tail = (tail + 1)%(ring_size+1);
    mutex.unlock();
    return true;
}

}

#endif