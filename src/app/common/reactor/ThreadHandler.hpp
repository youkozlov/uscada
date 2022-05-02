#pragma once

namespace app::reactor
{

class ThreadHandler
{
public:
    virtual ~ThreadHandler() {}

    virtual void run() = 0;
};


} // namespace app::reactor
