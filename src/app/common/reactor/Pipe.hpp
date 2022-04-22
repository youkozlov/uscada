#pragma once

#include <cstdint>

#include "FdHandler.hpp"
namespace reactor
{

class EpollInterface;
class PipeHandler;
struct PipeEvent;

class Pipe : public FdHandler
{
public:
    explicit Pipe(EpollInterface&, PipeHandler&);

    ~Pipe();

    void send(PipeEvent const&);

    int getFd() const final;

    void onEvent(int) final;

private:
    EpollInterface& epoll;
    PipeHandler& handler;
    int pipefd[2] = {};
};

} // namespace reactor
