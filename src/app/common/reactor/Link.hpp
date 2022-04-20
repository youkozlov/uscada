#pragma once

#include "LinkHandler.hpp"
#include "LinkInterface.hpp"
#include "Epoll.hpp"

namespace reactor
{

class Link : public LinkInterface
{
public:
    explicit Link(LinkHandler&, Epoll&);

    ~Link();

    int getFd() const final;

    void onEvent(int) final;

    void assignFd(int) final;

    void connect(LinkAddr const&) final;

    void close() final;

    int send(void const*, std::size_t) final;

    int receive(void*, std::size_t) final;

private:
    LinkHandler& handler;
    Epoll& epoll;
    int fd;
};

} // namespace reactor
