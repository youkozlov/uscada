#pragma once

namespace reactor
{

class ThreadHandler
{
public:
    virtual ~ThreadHandler() {}

    virtual void run() = 0;
};


} // namespace reactor
