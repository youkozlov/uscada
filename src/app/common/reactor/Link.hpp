#pragma once

#include "LinkHandler.hpp"
#include "LinkInterface.hpp"

namespace reactor
{

class EpollInterface;

class Link : public LinkInterface
{
public:
    explicit Link(EpollInterface&);

    ~Link();

    int getFd() const final;

    void onEvent(int) final;

    void assignFd(int) final;

    void connect(LinkAddr const&) final;

    void close() final;

    void release() final;

    int send(void const*, std::size_t) final;

    int receive(void*, std::size_t) final;

    void setHandler(LinkHandler*);

private:
    EpollInterface& epoll;
    LinkHandler* handler;
    int fd;
};

} // namespace reactor
