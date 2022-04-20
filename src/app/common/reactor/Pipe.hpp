#pragma once

#include <cstdint>

#include "FdHandler.hpp"
#include "Epoll.hpp"

namespace reactor
{

class PipeHandler;
struct PipeEvent;

class Pipe : public FdHandler
{
public:
    explicit Pipe(PipeHandler&, Epoll&);

    ~Pipe();

    void send(PipeEvent const&);

    int getFd() const final;

    void onEvent(int) final;

private:
    PipeHandler& handler;
    Epoll& epoll;
    int pipefd[2] = {};
};

} // namespace reactor
