#pragma once

namespace app::reactor
{

class TimerInterface
{
public:
    virtual ~TimerInterface() {}

    virtual void start(long) = 0;

    virtual void stop() = 0;

    virtual void release() = 0;
};

} // namespace app::reactor
