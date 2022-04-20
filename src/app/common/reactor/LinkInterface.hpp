#pragma once

#include <cstdint>
#include "FdHandler.hpp"
#include "LinkAddr.hpp"

namespace reactor
{

class LinkInterface : public FdHandler
{
public:
    virtual ~LinkInterface() {}

    virtual void assignFd(int) = 0;

    virtual void connect(LinkAddr const&) = 0;

    virtual void close() = 0;

    virtual int send(void const*, std::size_t) = 0;

    virtual int receive(void*, std::size_t) = 0;
};

} // namespace reactor
