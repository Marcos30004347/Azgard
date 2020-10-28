#include "Logger.hpp"
#include "Debugger.hpp"
#include "Runtime/TimeManager.hpp"

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

Azgard::ConcurrentQueue<LogMessage>* Logger::message_list  = nullptr;
Azgard::Thread* Logger::logger_thread = nullptr;
bool Logger::shouldLoggerLog = true;

void Logger::logLine(LogMessageType type, LogChannel chanel, const char * fmt, ...) {
    #if defined(AZGARD_DEBUG_BUILD)

    va_list arg;
    
    va_start (arg, fmt);
    char* buffer = new char[512];

    vsprintf(buffer, fmt, arg);
    va_end (arg);
    LogMessage message = LogMessage();

    message.message = buffer;
    message.time = TimeManager::getMillisecondsSinseEpoch();
    message.chanel = chanel;
    message.size = 0;
    message.type = type;

    Logger::message_list->pushBack(message);


    // #if defined(TRACY_ENABLE)
    // TracyMessage(buffer, size);
    // #endif

    // std::cout << "LOGLINE" << std::endl;
    #endif
}


void Logger::run(void *data) {
    #if defined(AZGARD_DEBUG_BUILD)
    AZG_DEBUGGER_SET_THREAD_NAME("DebuggerThread")

    LogMessage* tmp = nullptr;
    const char* color = defaultForegroundColor();

    while(Logger::shouldLoggerLog) {
        if(Logger::shouldLoggerLog == false) break;
        while((Logger::message_list->size() == 0) && (Logger::shouldLoggerLog == true)) {
            Azgard::Thread::thisThread::yield();
        }
    
        if(Logger::message_list->size() > 0){

            AZG_DEBUG_SCOPE_NAMED("log message")
            
            LogMessage message = Logger::message_list->popFront();
        
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

            Date date = TimeManager::getCurrentDate();

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
    Logger::message_list = new Azgard::ConcurrentQueue<LogMessage>();
    Logger::logger_thread = new Azgard::Thread(Logger::run, nullptr);
    #endif

}

void Logger::stopLoggerThread() {
    #if defined(AZGARD_DEBUG_BUILD)
    Logger::shouldLoggerLog = false;
    #endif

}

void Logger::waitPendingMessages() {
    // Wait untial all log messages have been logged
    while(Logger::message_list->size()) {
        // When the job system kicks out we should probably use other strategy here
        Azgard::Thread::thisThread::yield();
    }
}


void Logger::shutDown(bool force) {
    // #if defined(AZGARD_DEBUG_BUILD)

    if(!force) {
        Logger::waitPendingMessages();
    } else {
        delete Logger::message_list;
    }

    Logger::stopLoggerThread();
    Logger::logger_thread->join();
    Logger::logger_thread->close();
    // delete logger_thread;
    AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "ASDASDSDSD");

    // #endif
};