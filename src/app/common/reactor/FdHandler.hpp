#pragma once

namespace reactor
{

class FdHandler
{
public:

    virtual ~FdHandler() {}

    virtual int getFd() const = 0;

    virtual void onEvent(int) = 0;
};

} // namespace reactor
