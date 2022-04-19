#pragma once

#include "FdHandler.hpp"
#include "TimerHandler.hpp"
#include "TimerInterface.hpp"

namespace reactor
{

class ReactorInterface;

class Timer : public FdHandler, public TimerInterface
{
public:
    explicit Timer(TimerHandler);

    ~Timer();

    void start(long) final;

    void stop() final;

    int getFd() const final;

    void onEvent(int) final;

    void release();

private:
    TimerHandler handler;
    int fd;
};


} // namespace reactor
