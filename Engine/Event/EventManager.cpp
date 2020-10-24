#include "EventManager.hpp"
#include "Runtime/TimeManager.hpp"

#include "SDL2/include/SDL.h"

using namespace Azgard;

inline KeyCode azgardKeyCodeToSDLKeyCode(SDL_Keycode code) {
    return (KeyCode)code;
}

inline KeyMode azgardKeyModeToSDLKeyMode(Uint16 mod) {
    return (KeyMode)mod;
}



Thread* EventManager::eventWorker = nullptr;
bool EventManager::shoudPoolEvents = true;

void EventManager::eventWorkerRun(void* data) {
    while (true) {
        SDL_Event event;
        KeyPressedData keyPressedEvent;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                keyPressedEvent.type = 1;
                keyPressedEvent.keyCode = azgardKeyCodeToSDLKeyCode(event.key.keysym.sym);
                keyPressedEvent.timestamp = TimeManager::getProgramMilliseconds();
                keyPressedEvent.mode = azgardKeyModeToSDLKeyMode(event.key.keysym.mod);
                keyPressedEvent.repeat = event.key.repeat;
                keyPressedEvent.windowID = event.key.windowID;

                // dispatch the event
                Event<KeyPressedData>::dispatch(keyPressedEvent);

                break;
            case SDL_KEYUP:
                keyPressedEvent.type = 0;
                keyPressedEvent.keyCode = azgardKeyCodeToSDLKeyCode(event.key.keysym.sym);
                keyPressedEvent.timestamp = TimeManager::getProgramMilliseconds();
                keyPressedEvent.mode = azgardKeyModeToSDLKeyMode(event.key.keysym.mod);
                keyPressedEvent.repeat = event.key.repeat;
                keyPressedEvent.windowID = event.key.windowID;

                // dispatch the event
                Event<KeyPressedData>::dispatch(keyPressedEvent);

                break;
            
            default:
                break;
            }
            /* handle your event here */
        }
        /* do some other stuff here -- draw your app, etc. */
    }
}

void EventManager::startUp() {
    AZG_CORE_ASSERT_AND_REPORT(SDL_Init(SDL_INIT_EVENTS) != 0, "SDL Events Not initialized correctly!");
    EventManager::shoudPoolEvents = true;
    EventManager::eventWorker = new Thread(EventManager::eventWorkerRun, nullptr);
}

void EventManager::shutDown(){
    EventManager::shoudPoolEvents = false;
    EventManager::eventWorker->join();
    delete EventManager::eventWorker;
}