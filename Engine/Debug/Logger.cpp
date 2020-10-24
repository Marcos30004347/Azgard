#include "Logger.hpp"
#include "Debugger.hpp"

#include <iostream>
#include <stdio.h>
#include <cstdarg>

/**
Black        0;30     Dark Gray     1;30
Red          0;31     Light Red     1;31
Green        0;32     Light Green   1;32
Brown/Orange 0;33     Yellow        1;33
Blue         0;34     Light Blue    1;34
Purple       0;35     Light Purple  1;35
Cyan         0;36     Light Cyan    1;36
Light Gray   0;37     White         1;37
 */
const char* redForegroundColor() {return "\033[31m"; }
const char* yellowForegroundColor() {return "\x1b[33m"; }
const char* greenForegroundColor() {return "\033[32m"; }
const char* blueForegroundColor() {return "\033[34m"; }
const char* defaultForegroundColor() {return "\033[39m"; }
const char* redBackgroundColor() {return "\033[41m"; }
const char* greenBackgroundColor() {return "\033[42m"; }
const char* blueBackgroundColor() {return "\033[44m"; }
const char* defaultBackgroundColor() {return "\033[49m"; }

using namespace Azgard;

Azgard::SpinLock Logger::message_lock;
Azgard::Thread* Logger::logger_thread = nullptr;

LogMessage* Logger::tail = nullptr;
LogMessage* Logger::top = nullptr;

void Logger::logLine(LogMessageType type, LogChannel chanel, const char * fmt, ...) {
    #if defined(AZGARD_DEBUG_BUILD)

    va_list arg;
    va_start (arg, fmt);
    size_t size = snprintf( nullptr, 0, fmt, arg);
    char* buffer = new char[size];
    vsprintf(buffer, fmt, arg);
    
    LogMessage* message = new LogMessage();

    message->message = buffer;
    message->next = nullptr;
    message->parent = Logger::tail;
    message->time = 0; // @TODO: ADD MESSAGE TIME
    message->chanel = chanel;
    message->size = size;
    message->type = type;

    Logger::message_lock.lock();

    if(Logger::tail) Logger::tail->next = message;

    if(!Logger::top) Logger::top = message;
    else Logger::tail = message;

    Logger::message_lock.unlock();

    // #if defined(TRACY_ENABLE)
    // TracyMessage(buffer, size);
    // #endif

    va_end (arg);

    #endif
}


void Logger::run(void *data) {
    AZG_DEBUGGER_SET_THREAD_NAME("DebuggerThread")

    LogMessage* tmp = nullptr;
    const char* color = defaultForegroundColor();

    while(true) {
        while(!Logger::top) Azgard::Thread::thisThread::yield();

        while(Logger::top) {
            AZG_DEBUG_SCOPE_NAMED("log message")
            
            Logger::message_lock.lock();

            switch (Logger::top->type)
            {
            case LogMessageType::DEBUG:
                color = greenForegroundColor();
                break;
            case LogMessageType::WARNING:
                color = yellowForegroundColor();
                break;
            case LogMessageType::ERROR:
                color = redForegroundColor();
                break;
            default:
                color = defaultForegroundColor();
                break;
            }
        
            std::cout << color << "[" << LogChannelNames[Logger::top->chanel] << " - " << Logger::top->time << "]: " << defaultForegroundColor() << Logger::top->message << std::endl;
            
            tmp = Logger::top->next;
        
            delete Logger::top;
        
            Logger::top  = tmp;
        
            Logger::message_lock.unlock();
        }

    }
}


void Logger::startUp(){
    Logger::logger_thread = new Azgard::Thread(Logger::run, nullptr);
}

void Logger::shutDown(){
    Logger::logger_thread->close();
    delete logger_thread;
    LogMessage* tmp = Logger::top;

    Logger::message_lock.lock();

    while(Logger::top) {
        tmp = Logger::top->next;
        delete Logger::top;
        Logger::top = tmp;
    }

    Logger::message_lock.unlock();
};