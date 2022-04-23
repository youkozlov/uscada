#pragma once

namespace reactor
{

class EventHandler
{
public:
    virtual ~EventHandler() {}

    virtual void onFdEvent(uint64_t) = 0;
};

} // namespace reactor
