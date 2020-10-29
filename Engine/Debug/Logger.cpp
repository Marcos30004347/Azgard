#include "Logger.hpp"
#include "Debugger.hpp"
#include "Runtime/TimeManager.hpp"
#include "Library/String.hpp"

#include <iostream>
#include <sstream>
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

#define AZGARD_LOG_SYNC

void logMessage(LogMessage& message) {
    Date date = TimeManager::getSingletonPtr()->getDate(message.time);

    const char* color;

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

    std::stringstream stream("");

    stream <<
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
    "\n";

    printf("%s", stream.str().c_str());
    #if defined(TRACY_ENABLE)
    TracyMessage(stream.str().c_str(), stream.str().size());
    #endif
    delete message.message;
}

void Logger::logLine(LogMessageType type, LogChannel chanel, const char * fmt, ...) {
    #if defined(AZGARD_DEBUG_BUILD)

    va_list arg;
    
    va_start (arg, fmt);
    char* buffer = AZG_NEW char[512];

    vsprintf(buffer, fmt, arg);
    va_end (arg);

    LogMessage message = LogMessage();

    message.message = buffer;
    message.time = TimeManager::getSingletonPtr()->getMillisecondsSinseEpoch();
    message.chanel = chanel;
    message.size = Azgard::cStrLen(buffer);
    message.type = type;

    #ifdef AZGARD_LOG_SYNC
    logMessage(message);
    #else
    Logger::getSingletonPtr()->message_list->pushBack(message);
    #endif

    // std::cout << "LOGLINE" << std::endl;
    #endif
}


void Logger::run(void *data) {
    
    #if defined(AZGARD_DEBUG_BUILD) && !defined(AZGARD_LOG_SYNC)
    AZG_DEBUGGER_SET_THREAD_NAME("DebuggerThread")

    LogMessage* tmp = nullptr;
    const char* color = defaultForegroundColor();

    while(Logger::getSingletonPtr()->shouldLoggerLog) {
        if(Logger::getSingletonPtr()->shouldLoggerLog == false) break;
        while((Logger::getSingletonPtr()->message_list->size() == 0) && (Logger::shouldLoggerLog == true)) {
            Azgard::Thread::thisThread::yield();
        }
    
        if(Logger::getSingletonPtr()->message_list->size() > 0){

            AZG_DEBUG_SCOPE_NAMED("log message")
            
            LogMessage message = Logger::getSingletonPtr()->message_list->popFront();
            logMessage(message);
        }

    }  
    #endif

}

Logger::Logger() {
    #if defined(AZGARD_DEBUG_BUILD) && !defined(AZGARD_LOG_SYNC)
    this->shouldLoggerLog = true;
    this->message_list = AZG_NEW Azgard::ConcurrentQueue<LogMessage>();
    this->logger_thread = AZG_NEW Azgard::Thread(Logger::run, nullptr);
    #endif
}
Logger::~Logger() {
    #ifndef AZGARD_LOG_SYNC

    delete Logger::getSingletonPtr()->message_list;

    Logger::getSingletonPtr()->stopLoggerThread();
    Logger::getSingletonPtr()->logger_thread->join();
    Logger::getSingletonPtr()->logger_thread->close();

    delete Logger::getSingletonPtr()->logger_thread;
    #endif
}

void Logger::startUp(){
    Logger::gInstancePtr = new Logger();
}

void Logger::stopLoggerThread() {
    #if defined(AZGARD_DEBUG_BUILD)
    Logger::shouldLoggerLog = false;
    #endif

}

void Logger::waitPendingMessages() {
    // Wait untial all log messages have been logged
    #ifndef AZGARD_LOG_SYNC
    while(Logger::getSingletonPtr()->message_list->size()) {
        // When the job system kicks out we should probably use other strategy here
        Azgard::Thread::thisThread::yield();
    }
    #endif
}


void Logger::shutDown(bool force) {
    if(!force) {
        Logger::getSingletonPtr()->waitPendingMessages();
    }
    delete Logger::gInstancePtr;
};