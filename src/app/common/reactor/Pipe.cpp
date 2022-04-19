#include "Pipe.hpp"

#include <unistd.h>
#include <stdexcept>
#include <iostream>

#include "ReactorInterface.hpp"

namespace reactor
{

Pipe::Pipe(ReactorInterface& reactor_)
    : reactor(reactor_)
{
    if (::pipe2(pipefd, 0) == -1)
    {
        throw std::runtime_error("pipe2");
    }
}

Pipe::~Pipe()
{
    ::close(pipefd[0]);
    ::close(pipefd[1]);
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
    reactor.handlePipeEvent(ev);
}

int Pipe::getFd() const
{
    return pipefd[0];
}

} // namespace reactor
