#pragma once

#include "FdHandler.hpp"
#include "TimerHandler.hpp"
#include "TimerInterface.hpp"

namespace reactor
{

class EpollInterface;

class Timer : public FdHandler, public TimerInterface
{
public:
    explicit Timer(EpollInterface&);

    ~Timer();

    void create();

    void close();

    void setHandler(TimerHandler*);

private:

    void start(long) final;

    void stop() final;

    int getFd() const final;

    void onEvent(int) final;

    void release() final;

    EpollInterface& epoll;
    TimerHandler* handler;
    int fd;
};


} // namespace reactor
