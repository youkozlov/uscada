#pragma once

#include <cstring>
#include <cstdio>
#include <mutex>
#include <vector>

namespace app
{

enum class LogTask
{
    GEN = 0,
    CTRL,
    MODBUS,
    UATL,
    UASC,
    UASRV,
    UA,

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
    if (app::LogLevel::LM_LEVEL >= app::Logger::getInst().getTaskLogLevel(app::LogTask::LM_TASK)) \
    {\
        char temporary___[1024];\
        sprintf(temporary___, __VA_ARGS__);\
        app::Logger::getInst().dispatch(temporary___, app::LogLevel::LM_LEVEL, app::LogTask::LM_TASK, __FILE__, __LINE__);\
    }\
}

class Logger
{
public:

    static app::Logger& getInst();

    void setTaskLogLevel(LogTask, LogLevel);

    app::LogLevel getTaskLogLevel(app::LogTask) const;

    void dispatch(char const*, app::LogLevel, app::LogTask, char const*, int);

private:
    Logger();

    std::mutex mutex;
    static constexpr int numLogTasks = static_cast<int>(app::LogTask::NUM);
    std::vector<app::LogLevel> logLevels;
};

} // namespace app
