#include "Timer.hpp"

#include <stdexcept>
#include <sys/timerfd.h>
#include <unistd.h>
#include <sys/epoll.h>

#include "EpollInterface.hpp"

#include "Logger.hpp"

namespace reactor
{

Timer::Timer(EpollInterface& epoll_)
    : epoll(epoll_)
    , fd(-1)
{
}

Timer::~Timer()
{
    if (-1 != fd)
    {
        close();
    }
}

void Timer::create()
{
    if (-1 != fd)
    {
        throw std::runtime_error("already created");
    }
    fd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
    if (fd == -1)
    {
        throw std::runtime_error("timerfd_create");
    }
    if (-1 == epoll.add(*this, EPOLLIN | EPOLLET))
    {
        ::close(fd);
        throw std::runtime_error("fd add");
    }
}

void Timer::close()
{
    if (-1 == fd)
    {
        LM(GEN, LW, "fd is invalid");
        return;
    }
    LM(GEN, LD, "Close");
    if (-1 == epoll.del(*this))
    {
        LM(GEN, LE, "fd del errno: %d", errno);
    }
    if (-1 == ::close(fd))
    {
        LM(GEN, LE, "close errno: %d", errno);
    }
    fd = -1;
}

void Timer::setHandler(TimerHandler handler_)
{
    handler = handler_;
}

void Timer::start(long interval)
{
    struct timespec now;
    if (::clock_gettime(CLOCK_MONOTONIC, &now) == -1)
    {
        throw std::runtime_error("clock_gettime");
    }
    struct itimerspec new_value;
    long const nsec = interval * 1000L;
    long const nano = 1000000000L;
    new_value.it_value.tv_sec = now.tv_sec + (now.tv_nsec + nsec) / nano;
    new_value.it_value.tv_nsec = (now.tv_nsec + nsec) % nano;
    new_value.it_interval.tv_sec = 0;
    new_value.it_interval.tv_nsec = 0;
    if (::timerfd_settime(fd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
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

void Timer::release()
{
    stop();
    close();
    handler = {};
}

void Timer::onFileDescriptorEvent(int)
{
    if (not handler)
    {
        LM(GEN, LE, "Handler is undefined");
    }
    uint64_t exp;
    int rc = ::read(fd, &exp, sizeof(uint64_t));
    if (rc != sizeof(uint64_t))
    {
        throw std::runtime_error("read");
    }
    if (handler)
    {
        handler();
    }
}

int Timer::fileDescriptor() const
{
    return fd;
}

} // namespace reactor
