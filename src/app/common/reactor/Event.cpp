#include "Event.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <iostream>
#include <sys/epoll.h>
#include <sys/eventfd.h>

#include "EventHandler.hpp"
#include "Logger.hpp"

#include "EpollInterface.hpp"

namespace reactor
{

Event::Event(EpollInterface& epoll_, EventHandler& handler_)
    : epoll(epoll_)
    , handler(handler_)
    , fd(-1)
{
    fd = ::eventfd(0, 0);
    if (-1 == fd)
    {
        throw std::runtime_error("eventfd");
    }
    if (-1 == epoll.add(*this, EPOLLIN | EPOLLET))
    {
        throw std::runtime_error("fd add");
    }
}

Event::~Event()
{
    LM(GEN, LD, "Close");
    if (-1 == epoll.del(*this))
    {
        LM(GEN, LE, "fd del errno: %d", errno);
    }
    if (-1 == ::close(fd))
    {
        LM(GEN, LE, "close errno: %d", errno);
    }
}

void Event::send()
{
    std::uint64_t const u = 1;
    if (-1 == ::write(fd, &u, sizeof(u)))
    {
        throw std::runtime_error("write");
    }
}

void Event::onEvent(int)
{
    std::uint64_t u;
    if (sizeof(uint64_t) != ::read(fd, &u, sizeof(u)))
    {
        throw std::runtime_error("read");
    }
    handler.onFdEvent(u);
}

int Event::getFd() const
{
    return fd;
}

} // namespace reactor
