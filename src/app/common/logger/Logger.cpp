#include "Logger.hpp"

#include "stdio.h"
#include "stdlib.h"
#include <ctime>

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
    }
    return "INVALID";
}

} // namespace


Logger::Logger()
{}

Logger& Logger::getInst()
{
    static Logger inst;
    return inst;
}

LogLevel Logger::getTaskLogLevel(LogTask task) const
{
    return logLevels[static_cast<int>(task)];
}

void Logger::dispatch(char const* msg, LogLevel lvl, LogTask task, char const* file, int line)
{
    char strTimeInfo[80];
    time_t rawtime;
    time (&rawtime);
    struct tm * timeinfo = localtime(&rawtime);
    strftime(strTimeInfo, sizeof(strTimeInfo),"%d-%m-%Y %H:%M:%S",timeinfo);
    char const* filePart = strrchr(file, '/');
    char const* fileToLog = filePart ? filePart + 1 : file;

    std::lock_guard<std::mutex> guard(mutex);

    printf("%s %s [%s] %s %d: %s\n", strTimeInfo, toString(lvl), toString(task), fileToLog, line, msg);
}

} // namespace app
