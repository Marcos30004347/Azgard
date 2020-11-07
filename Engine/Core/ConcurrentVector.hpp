#ifndef AZGARD_LIB_ASYNC_VECTOR
#define AZGARD_LIB_ASYNC_VECTOR

#include "SpinLock.hpp"
#include "Engine.hpp"
#include "Math.hpp"


// #include<iostream>

namespace Azgard {

template<typename T, unsigned int max_increase = 10000> 
class ConcurrentVector {
    class Iterator {
        public:
        int first;
        T& second;

        Iterator& operator+(int i) {
            return Iterator(this->first+i, *(&this->second+i));
        }
        Iterator& operator++() {
            return Iterator(this->first++, *(&this->second++));
        }
        Iterator& operator-(int i) {
            return Iterator(this->first - i, *(&this->second-i));
        }
        Iterator& operator--() {
            return Iterator(this->first--, *(&this->second--));
        }
        private:
        Iterator(int index, T& val): first{index}, second{val} {}
        // friend class ConcurrentVector;
    };

private:
    SpinLock lock;
    T* _data = nullptr;
    unsigned int array_size = 0;
    unsigned int _length = 0;

    /**
     * @brief Increment current array to store more @size entities.
     * 
     * @param size Count of units to increment.
     */
    void increaseArray(unsigned int size) {
        lock.lock();
        T* new_array = new T[size + this->array_size];
        Azgard::copyBytes(this->_data, new_array, this->array_size);
        T* tmp = this->_data;
        this->_data = new_array;
        this->array_size += size;
        delete tmp;
        lock.unlock();
    }

public:
    ConcurrentVector(unsigned int reserve = 1) {
        this->array_size = reserve;
        this->_length = 0;
        this->_data = new T[reserve];
    }

    ~ConcurrentVector() {
        if(this->_data) delete this->_data;
    }
    void clearAndReserve(unsigned int size) {
        lock.lock();
        if(this->_data) delete this->_data;

        this->array_size = size;
        _data = new T[size];
        lock.unlock();
    }
    
    void clear() {
        this->array_size = 0;
        this->_length = 0;
        delete this->_data;
    }

    void pushBack(const T& value) {
        lock.lock();
        if(!this->_data) {
            this->_data = new T[10];
            this->array_size = 10;
        }
    
        if(!this->array_size > this->_length) {
            this->increaseArray(Azgard::clamp(this->_length/2, 0, max_increase));
        }
        this->_data[this->_length++] = value;
        lock.unlock();

    }

    void popBack(const T& value) {
        lock.lock();
        this->_length--;
        lock.unlock();
    }

    void pushFront(const T& value) {
        lock.lock();
        if(!this->_data) {
            this->_data = new T[10];
            this->array_size = 10;
        }
    
        if(!this->array_size > this->_length) {
            this->increaseArray(Azgard::clamp(this->_length/2, 0, max_increase));
        }
        Azgard::copyBytes(this->_data, this->_data + 1, this->_length);
        this->_data[0] = value;
        lock.unlock();
    }

    void popFront(const T& value) {
        lock.lock();
        Azgard::copyBytes(this->_data + 1, this->_data, this->_length - 1);
        lock.unlock();
    }

    T* data() {
        return this->_data;
    }

    inline unsigned int length() {
        return this->_length;
    }

    Iterator begin() {
        return Iterator(0, this->_data[0]);
    }

    Iterator end() {
        return Iterator(this->_length, this->_data[this->_length]);
    }

    Iterator at(int index) {
        return Iterator(index, this->_data[index]);
    }

    T& operator[](int index) {
        return this->_data[index];
    }
};

}

#endif