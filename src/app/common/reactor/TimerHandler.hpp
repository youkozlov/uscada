#pragma once

namespace reactor
{

class TimerHandler
{
public:
    virtual ~TimerHandler() {}

    virtual void onTimer() = 0;
};

} // namespace reactor
