#pragma once

#include "LinkHandler.hpp"
#include "FileDescriptorInterface.hpp"
#include "LinkInterface.hpp"

namespace app::reactor
{

class EpollInterface;

class Link : public LinkInterface
{
public:
    explicit Link(EpollInterface&);

    ~Link();

    void connect(LinkAddr const&) final;

    void close() final;

    void release() final;

    int send(void const*, std::size_t) final;

    LinkResult receive(std::uint8_t*, std::size_t) final;

    void setHandler(LinkHandler) final;

private:
    int fileDescriptor() const final;

    void setFileDescriptor(int) final;

    void onFileDescriptorEvent(int) final;

    EpollInterface& epoll;
    LinkHandler handler;
    int fd;
};

} // namespace app::reactor
