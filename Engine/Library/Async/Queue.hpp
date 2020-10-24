#ifndef AZGARD_LIB_ASYNC_LINKED_LIST
#define AZGARD_LIB_ASYNC_LINKED_LIST

#include "Core/Engine.hpp"
#include "Memory/MemoryManager.hpp"
#include "Library/SpinLock.hpp"
// #include<iostream>

namespace Azgard {


template<typename T> 
class AsyncQueue {
// TODO: Alocate AsyncLinkedList from pool.
private:
    class Item {
    public:
        // TODO: Alocate Items from pool.
        T value;
        Item* next = nullptr;
        Item* parent = nullptr;

        // void* operator new(long unsigned int size) { 
        //     return Azgard::MemoryManager::mallocFromGlobalPool(size); 
        // }

        // void operator delete(void* ptr) { 
        //     return Azgard::MemoryManager::freeInGlobalPool(ptr);
        // }
    };

    SpinLock lock;

    Item* top = nullptr;
    Item* tail = nullptr;
    unsigned int count = 0;
public:
    AsyncQueue(){}
    ~AsyncQueue(){
        this->lock.lock();

        Item* tmp;
        while(this->top) {
            tmp = this->top->next;
            delete this->top;
            this->top = tmp;
        }
        this->lock.unlock();

    }


    void pushBack(T &element) {
        
        this->lock.lock();

        Item* tmp = new Item();
        tmp->value = element;
        tmp->parent = this->tail;

        if(!this->top) this->top = tmp;
    
        if(!this->tail) {
            if(tmp != this->top) {
                this->top->next = tmp;
                this->tail = tmp;
            }
        } else {
            this->tail->next = tmp;
            tmp->parent = this->tail;
            this->tail = tmp;
        }

        count++;
        this->lock.unlock();
    }

    T popFront() {
        Item* tmp;
        this->lock.lock();

        tmp = this->top;
        this->top = this->top->next;
        count--;
    
        this->lock.unlock();
        T val = tmp->value;
        delete tmp;
        return val;
    }


    unsigned int size() {
        return this->count;
    }
    // AZGARD_OVERLOAD_NEW
    // AZGARD_OVERLOAD_DELETE

    // void* operator new(long unsigned int size) { 
    //     return Azgard::MemoryManager::mallocFromGlobalPool(size); 
    // }

    // void operator delete(void* ptr) { 
    //     return Azgard::MemoryManager::freeInGlobalPool(ptr);
    // }
};

}

#endif