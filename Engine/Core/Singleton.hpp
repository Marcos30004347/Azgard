#ifndef AZGARD_LIB_SINGLETON
#define AZGARD_LIB_SINGLETON

#include "Core/Engine.hpp"

template<typename T>
class Singleton {
protected:
    static T* gInstancePtr;
public:

    static T* getSingletonPtr() {
        // AZG_CORE_ASSERT_AND_REPORT(gInstancePtr != nullptr, "Singleton not started!");
        return Singleton<T>::gInstancePtr;
    }
};


template<typename T>
T* Singleton<T>::gInstancePtr = nullptr;

#endif