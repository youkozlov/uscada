#pragma once

#include "ComponentId.hpp"
#include "MsgId.hpp"

namespace app::reactor
{

struct MsgInterface
{
    virtual ~MsgInterface() {}

    virtual MsgId getMsgId() const = 0;

    virtual ComponentId getCompId() const = 0;

    virtual std::size_t size() const = 0;
};

}