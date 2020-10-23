#ifndef AZGARD_LIB_SINGLETON
#define AZGARD_LIB_SINGLETON

namespace Azgard {

template<typename T>
class Singleton {
public:
    static void startUp() {
        singleton_ptr = new T();
    }

    static void shutDown() {
        delete singleton_ptr;
    }

    static T* getSingletonPointer() {
        return singleton_ptr;
    }

    static T getSingletonInstance() {
        return *singleton_ptr;
    }

private:
    static T* singleton_ptr;
};

template<typename T>
T* Singleton<T>::singleton_ptr = nullptr;

}


#endif