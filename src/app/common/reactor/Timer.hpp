#pragma once

#include "FdHandler.hpp"
#include "TimerHandler.hpp"
#include "TimerInterface.hpp"
#include "Epoll.hpp"

namespace reactor
{

class ReactorInterface;

class Timer : public FdHandler, public TimerInterface
{
public:
    explicit Timer(TimerHandler, Epoll&);

    ~Timer();

    void start(long) final;

    void stop() final;

    int getFd() const final;

    void onEvent(int) final;

private:
    TimerHandler handler;
    Epoll& epoll;
    int fd;
};


} // namespace reactor
