#pragma once

#include <cstring>
#include <cstdio>
#include <mutex>

namespace app
{

enum class LogTask
{
    GEN = 0,
    CTRL,
    MODBUS,

    NUM
};

enum class LogLevel
{
    LD = 0,
    LI,
    LW,
    LE,
    NA
};

#define LM(LM_TASK, LM_LEVEL, ...) \
{ \
    if (LogLevel::LM_LEVEL >= Logger::getInst().getTaskLogLevel(LogTask::LM_TASK)) \
    {\
        char msg[256] = {};\
        sprintf(msg, __VA_ARGS__);\
        Logger::getInst().dispatch(msg, LogLevel::LM_LEVEL, LogTask::LM_TASK, __FILE__, __LINE__);\
    }\
}

class Logger
{
public:

    static Logger& getInst();

    LogLevel getTaskLogLevel(LogTask) const;

    void dispatch(char const*, LogLevel, LogTask, char const*, int);

private:
    Logger();

    std::mutex mutex;
    static constexpr int numLogTasks = static_cast<int>(LogTask::NUM);
    LogLevel logLevels[numLogTasks] = {};
};

} // namespace app
