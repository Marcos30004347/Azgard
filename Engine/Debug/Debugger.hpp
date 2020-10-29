#ifndef AZGARD_DEBUGGER
#define AZGARD_DEBUGGER

#ifdef TRACY_ENABLE
#include "tracy/Tracy.hpp"
#endif


namespace Azgard {

/**
 * Azgard Debugger currently is just an abstraction above tracy profiler(https://github.com/wolfpld/tracy),
 * please take a look at it and its manual for better understanding.
 * 
 * For debugging, you should run Tracy Profiler with the engine.
 */

/**
 * @brief Debugger main class
 * 
 * @note Do not use this class directly in your code, use the macros defined after the class instead.
 */
class Debugger {
public:
    /**
     * @brief Set the debug thread name
     * 
     * @param name The thread name
     */
    static void setThreadName(const char* name);

    /**
     * @brief Get the Thread Name by thread id.
     * 
     * @param thread_id The thread id to retrieve the name of.
     * @return The name of the thread with id @thread_id
     */
    static const char* getThreadName(unsigned int thread_id);

    /**
     * @brief Report to tracy that a secondary frame with name @frame_name has start.
     * 
     * @param frame_name The name of the frame that has just begun.
     */
    static void reportSecondaryFrameStart(const char* frame_name);
    
    /**
     * @brief Report to tracy that a secondary frame with name @frame_name has ended.
     * 
     * @param frame_name The name of the frame that has just ended.
     */
    static void reportSecondaryFrameEnd(const char* frame_name);

    /**
     * @brief Report That a Frame has just ended.
     */
    static void reportFrame();

};

}


#ifdef AZGARD_DEBUG_BUILD

#define AZG_DEBUGGER_SET_THREAD_NAME(name) Azgard::Debugger::setThreadName(name);
#define AZG_DEBUGGER_GET_THREAD_NAME(id) Azgard::Debugger::getThreadName(id);
#define AZG_DEBUGGER_SECONDARY_FRAME_START(name) Azgard::Debugger::reportSecondaryFrameStart(name);
#define AZG_DEBUGGER_SECONDARY_FRAME_END(name) Azgard::Debugger::reportSecondaryFrameEnd(name);
#define AZG_DEBUGGER_FRAME_MARK Azgard::Debugger::reportFrame();


#ifdef TRACY_ENABLE

// Tracy abstraction macros
#define AZG_DEBUG_SCOPE_NAMED(name) ZoneScopedN(name)
#define AZG_DEBUG_SCOPE ZoneScoped
#define AZG_DEBUG_MALLOC(ptr, size) TracyAlloc(ptr , size);
#define AZG_DEBUG_FREE(prt) TracyFree(ptr);

#elif


#define AZG_DEBUG_MALLOC(ptr, size)
#define AZG_DEBUG_FREE(prt)
#define AZG_DEBUG_SCOPE_NAMED(name)
#define AZG_DEBUG_SCOPE

#endif // TRACY_ENABLE

#if defined(_MSC_VER)
    extern void __cdecl __debugbreak(void);
    #define AZG_TRIGGER_BREAKPOINT __debugbreak()
#elif ( (!defined(__NACL__)) && ((defined(__GNUC__) || defined(__clang__)) && (defined(__i386__) || defined(__x86_64__))) )
    #define AZG_TRIGGER_BREAKPOINT __asm__ __volatile__ ( "int $3\n\t" )
#elif defined(__386__) && defined(__WATCOMC__)
    #define AZG_TRIGGER_BREAKPOINT { _asm { int 0x03 } }
#elif defined(HAVE_SIGNAL_H) && !defined(__WATCOMC__)
    #include <signal.h>
    #define AZG_TRIGGER_BREAKPOINT raise(SIGTRAP)
#else
    /* How do we trigger breakpoints on this platform? */
    #define AZG_TRIGGER_BREAKPOINT
#endif

#else // AZGARD_DEBUG_BUILD


#define AZG_DEBUG_SCOPE_NAMED(name)
#define AZG_DEBUG_SCOPE
#define AZG_DEBUGGER_SET_THREAD_NAME(name)
#define AZG_DEBUGGER_SECONDARY_FRAME_START(name)
#define AZG_DEBUGGER_SECONDARY_FRAME_END(name)
#define AZG_DEBUGGER_FRAME_MARK
#define AZG_DEBUG_SCOPE_NAMED(name)
#define AZG_DEBUG_SCOPE
#define AZG_DEBUG_MALLOC(ptr, size)
#define AZG_DEBUG_FREE(prt)
#define AZG_TRIGGER_BREAKPOINT

#endif // AZGARD_DEBUG_BUILD

#endif