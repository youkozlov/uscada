#include "Timer.hpp"

#include <stdexcept>
#include <sys/timerfd.h>
#include <unistd.h>

namespace reactor
{

Timer::Timer(TimerHandler handler_)
    : handler(handler_)
{
    fd = ::timerfd_create(CLOCK_REALTIME, 0);
    if (fd == -1)
    {
        throw std::runtime_error("timerfd_create");
    }
}

Timer::~Timer()
{
    if (-1 != fd)
    {
        ::close(fd);
    }
}

void Timer::start(long interval)
{
    struct timespec now;
    if (clock_gettime(CLOCK_REALTIME, &now) == -1)
    {
        throw std::runtime_error("clock_gettime");
    }
    struct itimerspec new_value;
    long const nsec = interval * 1000L;
    long const nano = 1000000000L;
    new_value.it_value.tv_sec = now.tv_sec + (now.tv_nsec + nsec) / nano;
    new_value.it_value.tv_nsec = (now.tv_nsec + nsec) % nano;
    new_value.it_interval.tv_sec = nsec / nano;
    new_value.it_interval.tv_nsec = nsec % nano;
    if (timerfd_settime(fd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
    {
        throw std::runtime_error("timerfd_settime");
    }
}

void Timer::stop()
{
    struct itimerspec new_value;
    new_value.it_value.tv_sec = 0;
    new_value.it_value.tv_nsec = 0;
    new_value.it_interval.tv_sec = 0;
    new_value.it_interval.tv_nsec = 0;
    if (timerfd_settime(fd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
    {
        throw std::runtime_error("timerfd_settime");
    }
}

void Timer::onEvent(int)
{
    uint64_t exp;
    if (sizeof(uint64_t) != ::read(fd, &exp, sizeof(uint64_t)))
    {
        throw std::runtime_error("read");
    }
    if (handler)
    {
        handler();
    }
}

int Timer::getFd() const
{
    return fd;
}

void Timer::release()
{
    handler = {};
}

} // namespace reactor
