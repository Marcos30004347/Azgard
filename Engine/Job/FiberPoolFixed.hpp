#ifndef JOBIN_FIBER_POOL_fixed_H
#define JOBIN_FIBER_POOL_fixed_H

//Local libraries
#include "Fiber.hpp"
#include <stdio.h>

namespace Azgard {

template<unsigned int size = 256>
class AvaliableIndicesStack {

private:
    unsigned int buff[size];
    unsigned int top;

public:
    AvaliableIndicesStack(): top{0} {
        for(int i=0; i<size; i++) makeAvaliable(i);
    }

    ~AvaliableIndicesStack() {} // delete buff

    bool makeAvaliable(unsigned int i) {
        if (top == size) return false;
        buff[top] = i;
        top++;
        return true;
    }

    bool getAvaliable(unsigned int &i) {
        if(top == 0) return false;
        top--;
        i = buff[top];
        return true;
    }
};

template<unsigned int size = 256>
class FiberPoolFixed {
    Fiber buff[size];
    AvaliableIndicesStack<size> availableIds;

public:

    FiberPoolFixed();
    ~FiberPoolFixed();

    bool release(Fiber* &data);
    Fiber* request();

};

template<unsigned int size>
FiberPoolFixed<size>::FiberPoolFixed(): avaliableIds{} {}


template<unsigned int size>
FiberPoolFixed<size>::~FiberPoolFixed() {
    availableIds.~AvaliableIndicesStack();
}

template<unsigned int size>
bool FiberPoolFixed<size>::release(Fiber* &data) {
    if (!availableIds.makeAvaliable(data - buff)) return false;
    return true;
}

template<unsigned int size>
Fiber* FiberPoolFixed<size>::request() {
    unsigned int id;
    while (!availableIds.getAvaliable(id)) {}
    return buff + id;
}

}

#endif