#pragma once

#include <cstdint>
#include "LinkAddr.hpp"

namespace reactor
{

class LinkInterface
{
public:
    virtual ~LinkInterface() {}

    virtual void connect(LinkAddr const&) = 0;

    virtual void close() = 0;

    virtual void send(void const*, std::size_t) = 0;

    virtual int receive(void*, std::size_t) = 0;
};

} // namespace reactor
