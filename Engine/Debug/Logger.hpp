#ifndef AZGARD_LOGGER
#define AZGARD_LOGGER

#include "Library/SpinLock.hpp"
#include "Library/Thread.hpp"
// #include "Library/Singleton.hpp"

namespace Azgard {

enum LogChannel {
    GERAL0_CHANNEL = 0,
    GERAL1_CHANNEL,
    GERAL2_CHANNEL,
    GERAL3_CHANNEL,
    GERAL4_CHANNEL,
    GERAL5_CHANNEL,
    GERAL6_CHANNEL,
    RENDERING_CHANNEL,
    PHYSICS_CHANNEL,
    PLATFORM_CHANNEL,
    AUDIO_CHANNEL,
    CORE_CHANNEL
};

static const char* LogChannelNames[] = {
    "Geral0",
    "Geral1",
    "Geral2",
    "Geral3",
    "Geral4",
    "Geral5",
    "Geral6",
    "Rendering",
    "Physics",
    "Platform",
    "Audio",
    "Core",
};

enum LogMessageType {
    DEBUG = 0,
    ERROR,
    WARNING,
};

class LogMessage {
public:
    char* message = nullptr;
    unsigned int time;
    unsigned int size;
    LogMessageType type;
    LogChannel chanel;
    LogMessage* next = nullptr;
    LogMessage* parent = nullptr;
    ~LogMessage() {
        delete message;
    }
};

class Logger {

    static LogMessage* tail;
    static LogMessage* top;

    static Azgard::SpinLock message_lock;
    static Azgard::Thread* logger_thread;

    static void run(void* data);

public:
    /**
     * @brief Logs a formated string
     */
    static void logLine(LogMessageType type, LogChannel chanel, const char* fmt, ...);
    static void startUp();
    static void shutDown();
};

}

#ifdef AZG_DEBUG_BUILD
#define AZGARD_LOG(chanel, fmt, ...) Azgard::Logger::logLine(LogMessageType::DEBUG, chanel, fmt __VA_OPT__(,) __VA_ARGS__)
#define AZGARD_LOG_ERROR(chanel, fmt, ...) Azgard::Logger::logLine(LogMessageType::ERROR, chanel, fmt __VA_OPT__(,) __VA_ARGS__)
#define AZGARD_LOG_WARNING(chanel, fmt, ...) Azgard::Logger::logLine(LogMessageType::WARNING, chanel, fmt __VA_OPT__(,) __VA_ARGS__)
#else
#define AZGARD_LOG(chanel, fmt, ...) 
#define AZGARD_LOG_ERROR(chanel, fmt, ...)
#define AZGARD_LOG_WARNING(chanel, fmt, ...)
#endif


#endif