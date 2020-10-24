#ifndef AZGARD_EVENT_MANAGER
#define AZGARD_EVENT_MANAGER

#include "Library/Async/Vector.hpp"
#include "Library/Thread.hpp"
#include "Input/KeyCode.hpp"

namespace Azgard {


struct KeyPressedData {
    int type;
    int timestamp;
    int windowID;
    char state;
    char repeat;
    KeyCode keyCode;
    KeyMode mode;
};

typedef void(*EventCallback)(void*);

template<typename EventData>
class Event {
private:
    static AsyncVector<EventCallback> callbacks;

public:
    static void dispatch(EventData data) {
        for(int i=0; i<callbacks.length(); i++) {
            ((void(*)(EventData))Event<EventData>::callbacks[i])(data);
        }
    }

    static void registerCallback(void(*callback)(EventData)) {
        Event<EventData>::callbacks.pushBack((EventCallback)callback);

    }

};

template<typename EventData>
AsyncVector<EventCallback> Event<EventData>::callbacks;



class EventManager {
friend class Engine;

private:
    static bool shoudPoolEvents;
    static Thread* eventWorker;
    static void eventWorkerRun(void* data);
    static void startUp();
    static void shutDown();
public:

};

}

#endif
