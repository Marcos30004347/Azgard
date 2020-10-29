#ifndef AZGARD_ENGINE_RUNTIME
#define AZGARD_ENGINE_RUNTIME

#include "Core/Engine.hpp"


namespace Azgard {
    
class Engine {
    static void startUp();
    static void shutDown();
public:
    Engine();
    ~Engine();
};

}




// #define AZGARD_SETUP() \
// static constructor(initEngine); \
// void initEngine() { \
//     Azgard::Engine::startUp(); \
// }\
// static destructor(shutDownEngine); \
// void shutDownEngine() { \
//     Azgard::Engine::shutDown(); \
// } \


#endif