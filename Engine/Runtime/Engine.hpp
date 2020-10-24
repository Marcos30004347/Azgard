#ifndef AZGARD_ENGINE_RUNTIME
#define AZGARD_ENGINE_RUNTIME

#include "Core/Engine.hpp"

namespace Azgard {
    
class Engine {
public:
    AZG_API static void startUp();
    AZG_API static void shutDown();
};

}


#endif