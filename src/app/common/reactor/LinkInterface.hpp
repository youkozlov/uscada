#pragma once

#include <cstdint>
#include "FileDescriptorInterface.hpp"
#include "LinkAddr.hpp"

namespace reactor
{

class LinkInterface : public FileDescriptorInterface
{
public:
    virtual ~LinkInterface() {}

    virtual void connect(LinkAddr const&) = 0;

    virtual void close() = 0;

    virtual void release() = 0;

    virtual int send(void const*, std::size_t) = 0;

    virtual int receive(std::uint8_t*, std::size_t) = 0;
};

} // namespace reactor
