#include "Logger.hpp"

#include "stdio.h"
#include "stdlib.h"
#include <ctime>
#include <sys/time.h>

namespace app
{

namespace
{

char const* toString(LogLevel lvl)
{
    switch(lvl)
    {
    case LogLevel::LD:
        return "DBG";
    case LogLevel::LI:
        return "INF";
    case LogLevel::LW:
        return "WRN";
    case LogLevel::LE:
        return "ERR";
    case LogLevel::NA:
        return "NA";
    }
    return "INVALID";
}

char const* toString(LogTask task)
{
    switch(task)
    {
    case LogTask::GEN:
        return "GEN";
    case LogTask::CTRL:
        return "CTRL";
    case LogTask::MODBUS:
        return "MODBUS";
    case LogTask::UA:
        return "UA";
    case LogTask::NUM:
        return "Invalid";
    }
    return "INVALID";
}

} // namespace


Logger::Logger()
    : logLevels(numLogTasks, LogLevel::LD)
{
//    setTaskLogLevel(LogTask::GEN, LogLevel::LI);
    setTaskLogLevel(LogTask::MODBUS, LogLevel::NA);
    setTaskLogLevel(LogTask::CTRL, LogLevel::NA);
}

Logger& Logger::getInst()
{
    static Logger inst;
    return inst;
}

void Logger::setTaskLogLevel(LogTask task, LogLevel lvl)
{
    logLevels[static_cast<int>(task)] = static_cast<LogLevel>(lvl);
}

LogLevel Logger::getTaskLogLevel(LogTask task) const
{
    return logLevels[static_cast<int>(task)];
}

void Logger::dispatch(char const* msg, LogLevel lvl, LogTask task, char const* file, int line)
{
    std::lock_guard<std::mutex> guard(mutex);

    char strTimeInfo[80];

    struct timeval tv;
    struct tm* timeinfo;
    gettimeofday(&tv, NULL);

    timeinfo = ::localtime(&tv.tv_sec);
    strftime(strTimeInfo, sizeof(strTimeInfo),"%d-%m-%Y %H:%M:%S",timeinfo);
    char const* filePart = strrchr(file, '/');
    char const* fileToLog = filePart ? filePart + 1 : file;

    printf("%s.%03ld %s [%s] %s %d: %s\n", strTimeInfo, tv.tv_usec/1000, toString(lvl), toString(task), fileToLog, line, msg);
}

} // namespace app
