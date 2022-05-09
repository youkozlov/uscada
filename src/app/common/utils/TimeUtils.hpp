#pragma once

#include <cstdint>
#include <sys/time.h>

namespace app::utils
{

inline std::int64_t getCurrentDateTime()
{
    struct timeval tv;
    ::gettimeofday(&tv, NULL);

    //1601-01-01 12:00AM UTC
    //1700-01-01 12:00AM UTC
    //31 536 000
    //86400

    constexpr int64_t secsStdYear = 31536000;
    constexpr int64_t secsExtYearDiff = 86400;
    constexpr int64_t extYearPeriod = 4;
    constexpr int64_t yearStartLinux = 1970;
    constexpr int64_t yearStartOpcUa = 1601;
    constexpr int64_t yearCorrection = yearStartLinux - yearStartOpcUa;
    // to exclude ext correction in 1700, 1800, 1900
    constexpr int64_t extYearCorrection = 3;
    constexpr int64_t numExtYearsWithinCorrection = (yearStartLinux - yearStartOpcUa) / extYearPeriod - extYearCorrection;
    constexpr int64_t secsCorrection = yearCorrection * secsStdYear + numExtYearsWithinCorrection * secsExtYearDiff;

    return (tv.tv_sec + secsCorrection) * 1000 * 1000 * 10 + (tv.tv_usec % (1000 * 1000)) * 10;
}

} // namespace app::utils
