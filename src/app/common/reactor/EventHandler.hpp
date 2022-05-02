#pragma once

namespace app::reactor
{

class EventHandler
{
public:
    virtual ~EventHandler() {}

    virtual void onFdEvent(uint64_t) = 0;
};

} // namespace app::reactor
