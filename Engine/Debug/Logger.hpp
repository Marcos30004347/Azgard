#ifndef AZGARD_LOGGER
#define AZGARD_LOGGER

// #include "Library/SpinLock.hpp"
#include "Core/ConcurrentQueue.hpp"
#include "Core/Thread.hpp"
#include "Core/Singleton.hpp"

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
    long time;
    unsigned int size;
    LogMessageType type;
    LogChannel chanel;
};

class Logger: public Singleton<Logger> {
    bool shouldLoggerLog;

    ConcurrentQueue<LogMessage>* message_list;
    Azgard::Thread* logger_thread;

    void run(void* data);
    void stopLoggerThread();
    Logger();
    ~Logger();
public:
    /**
     * @brief Logs a formated string
     */
    void logLine(LogMessageType type, LogChannel chanel, const char* fmt, ...);
    void waitPendingMessages();

    static void startUp();
    static void shutDown(bool force = false);
};

}

#ifdef AZGARD_DEBUG_BUILD
#define AZG_LOG(fmt, ...) Azgard::Logger::getSingletonPtr()->logLine(Azgard::LogMessageType::DEBUG, Azgard::LogChannel::CORE_CHANNEL, fmt __VA_OPT__(,) __VA_ARGS__)
#define AZG_LOG_DEBUG(chanel, fmt, ...) Azgard::Logger::getSingletonPtr()->logLine(Azgard::LogMessageType::DEBUG, chanel, fmt __VA_OPT__(,) __VA_ARGS__)
#define AZG_LOG_ERROR(chanel, fmt, ...) Azgard::Logger::getSingletonPtr()->logLine(Azgard::LogMessageType::ERROR, chanel, fmt __VA_OPT__(,) __VA_ARGS__)
#define AZG_LOG_WARNING(chanel, fmt, ...) Azgard::Logger::getSingletonPtr()->logLine(Azgard::LogMessageType::WARNING, chanel, fmt __VA_OPT__(,) __VA_ARGS__)
#else
#define AZG_LOG(fmt, ...) 
#define AZG_LOG_DEBUG(chanel, fmt, ...) 
#define AZG_LOG_ERROR(chanel, fmt, ...)
#define AZG_LOG_WARNING(chanel, fmt, ...)
#endif


#endif