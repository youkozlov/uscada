#pragma once

#include <cstdint>
#include "FileDescriptorInterface.hpp"
#include "LinkAddr.hpp"
#include "LinkHandler.hpp"

namespace app::reactor
{

struct LinkResult
{
    enum
    {
          na = -2
        , error = -1
        , closed = 0
        , ok = 1
    } status;
    int len;
};

class LinkInterface : public FileDescriptorInterface
{
public:
    virtual ~LinkInterface() {}

    virtual void connect(LinkAddr const&) = 0;

    virtual void close() = 0;

    virtual void release() = 0;

    virtual int send(void const*, std::size_t) = 0;

    virtual LinkResult receive(std::uint8_t*, std::size_t) = 0;

    virtual void setHandler(LinkHandler) = 0;
};

} // namespace app::reactor
