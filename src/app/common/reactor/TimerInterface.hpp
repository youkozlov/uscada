#pragma once

namespace reactor
{

class TimerInterface
{
public:
    virtual ~TimerInterface() {}

    virtual void start(long) = 0;

    virtual void stop() = 0;
};

} // namespace reactor
