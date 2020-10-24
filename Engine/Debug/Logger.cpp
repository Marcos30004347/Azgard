#include "Logger.hpp"
#include "Debugger.hpp"
#include "Library/Time.hpp"

#include <iostream>
#include <stdio.h>
#include <cstdarg>

#define AZGARD_DEBUG_BUILD

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

Azgard::AsyncQueue<LogMessage> Logger::message_list;
Azgard::Thread* Logger::logger_thread = nullptr;
bool Logger::shouldLoggerLog = true;

void Logger::logLine(LogMessageType type, LogChannel chanel, const char * fmt, ...) {
    #if defined(AZGARD_DEBUG_BUILD)
    // Logger::message_lock.lock();


    va_list arg;
    va_start (arg, fmt);
    size_t size = snprintf( nullptr, 0, fmt, arg);
    char* buffer = new char[size];
    vsprintf(buffer, fmt, arg);
    
    LogMessage message = LogMessage();

    message.message = buffer;
    message.time = Time::getMillisecondsSinseEpoch();
    message.chanel = chanel;
    message.size = size;
    message.type = type;

    Logger::message_list.pushBack(message);


    // #if defined(TRACY_ENABLE)
    // TracyMessage(buffer, size);
    // #endif

    va_end (arg);
    // std::cout << "LOGLINE" << std::endl;
    #endif
}


void Logger::run(void *data) {
    #if defined(AZGARD_DEBUG_BUILD)
    AZG_DEBUGGER_SET_THREAD_NAME("DebuggerThread")

    LogMessage* tmp = nullptr;
    const char* color = defaultForegroundColor();

    while(Logger::shouldLoggerLog > 0) {
        if(Logger::shouldLoggerLog == false) break;
        while((Logger::message_list.size() == 0) && (Logger::shouldLoggerLog == true)) {
            Azgard::Thread::thisThread::yield();
        }
    
        if(Logger::message_list.size() > 0){

            AZG_DEBUG_SCOPE_NAMED("log message")
            
            LogMessage message = Logger::message_list.popFront();
        
            switch (message.type)
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

            Date date = Time::getDate(message.time);

            std::cout <<
            defaultForegroundColor() <<
            "[" <<
            LogChannelNames[message.chanel] <<
            " " <<
            date.hour <<
            ":" <<
            date.minutes <<
            ":" <<
            date.seconds <<
            "]: " <<
            color <<
            message.message <<
            defaultForegroundColor() <<
            std::endl;
            delete message.message;
        }

    }  
    #endif

}


void Logger::startUp(){
    #if defined(AZGARD_DEBUG_BUILD)
    Logger::shouldLoggerLog = true;
    Logger::logger_thread = new Azgard::Thread(Logger::run, nullptr);
    #endif

}

void Logger::stopLoggerThread() {
    #if defined(AZGARD_DEBUG_BUILD)
    Logger::shouldLoggerLog = false;
    #endif

}

void Logger::waitPendingMessages() {
    while(Logger::message_list.size()) {
        Azgard::Thread::thisThread::yield();
    } // Wait untial all log messages have been logged
}


void Logger::shutDown(bool force) {
    #if defined(AZGARD_DEBUG_BUILD)

    if(!force) {
        Logger::waitPendingMessages();
    } else {
        Logger::message_list.~AsyncQueue();
    }

    Logger::stopLoggerThread();
    Logger::logger_thread->join();
    Logger::logger_thread->close();
    // delete logger_thread;

    #endif
};