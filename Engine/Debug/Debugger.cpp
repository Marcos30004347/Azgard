#include "Debugger.hpp"

using namespace Azgard;

void Debugger::reportFrame() {
    #ifdef AZGARD_DEBUG_BUILD
    FrameMark;
    #endif
}

const char* Debugger::getThreadName(unsigned int thread_id) {
    #if defined(AZGARD_DEBUG_BUILD) && defined(TRACY_ENABLE)
    return tracy::GetThreadName(thread_id);
    #endif
    return nullptr;
}

void Debugger::setThreadName(const char* name) {
    #if defined(AZGARD_DEBUG_BUILD) && defined(TRACY_ENABLE)
    tracy::SetThreadName(name);
    #endif
}

void Debugger::reportSecondaryFrameStart(const char* name) {
    #if defined(AZGARD_DEBUG_BUILD) && defined(TRACY_ENABLE)
    FrameMarkStart(name)
    #endif
}

void Debugger::reportSecondaryFrameEnd(const char* name) {
    #if defined(AZGARD_DEBUG_BUILD) && defined(TRACY_ENABLE)
    FrameMarkEnd(name)
    #endif
}
