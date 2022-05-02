#pragma once

#include "LinkInterface.hpp"

namespace app::reactor
{

class AcceptorInterface
{
public:
    virtual ~AcceptorInterface() {}

    virtual void listen(LinkAddr const&) = 0;

    virtual void accept(LinkInterface&) = 0;

    virtual void close() = 0;

    virtual void release() = 0;
};

} // namespace app::reactor
