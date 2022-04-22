#include "Pipe.hpp"

#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <sys/epoll.h>

#include "PipeHandler.hpp"
#include "Logger.hpp"

#include "EpollInterface.hpp"

namespace reactor
{

Pipe::Pipe(EpollInterface& epoll_, PipeHandler& handler_)
    : epoll(epoll_)
    , handler(handler_)
{
    if (::pipe2(pipefd, 0) == -1)
    {
        throw std::runtime_error("pipe2");
    }
    if (-1 == epoll.add(*this, EPOLLIN | EPOLLET))
    {
        throw std::runtime_error("fd add");
    }
}

Pipe::~Pipe()
{
    LM(GEN, LD, "Close");
    if (-1 == epoll.del(*this))
    {
        LM(GEN, LE, "fd del errno: %d", errno);
    }
    if (-1 == ::close(pipefd[0]))
    {
        LM(GEN, LE, "close errno: %d", errno);
    }
    if (-1 == ::close(pipefd[1]))
    {
        LM(GEN, LE, "close errno: %d", errno);
    }
}

void Pipe::send(PipeEvent const& ev)
{
    ::write(pipefd[1], &ev, sizeof(PipeEvent));
}

void Pipe::onEvent(int)
{
    PipeEvent ev;
    if (sizeof(PipeEvent) != ::read(pipefd[0], &ev, sizeof(PipeEvent)))
    {
        throw std::runtime_error("read");
    }
    handler.onPipeEvent(ev);
}

int Pipe::getFd() const
{
    return pipefd[0];
}

} // namespace reactor
