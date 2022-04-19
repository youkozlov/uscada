#include "Link.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>

namespace reactor
{

Link::Link(LinkHandler& handler_, Epoll& epoll_)
    : handler(handler_)
    , epoll(epoll_)
    , fd(-1)
{
}

Link::~Link()
{
    if (-1 != fd)
    {
        ::close(fd);
    }
}

void Link::connect(LinkAddr const&)
{
    if (-1 != fd)
    {
        throw std::runtime_error("already connected");
    }
    fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == fd)
    {
        throw std::runtime_error("socket");
    }
    if (-1 == ::fcntl(fd, F_SETFL, O_NONBLOCK))
    {
        ::close(fd);
        fd = -1;
        throw std::runtime_error("fcntl");
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    int rc = ::connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if (0 != rc && EINPROGRESS != errno)
    {
        ::close(fd);
        fd = -1;
        throw std::runtime_error("connect");
    }
    epoll.add(*this, EPOLLIN | EPOLLOUT);
}

void Link::close()
{
    if (-1 == fd)
    {
        throw std::runtime_error("invalid fd");
    }
    epoll.del(*this);
    ::close(fd);
    fd = -1;
}

void Link::send(void const* data, std::size_t len)
{
    if (-1 == fd)
    {
        throw std::runtime_error("invalid fd");
    }
    if (-1 == ::write(fd, data, len))
    {
        throw std::runtime_error("write");
    }
}

int Link::receive(void*, std::size_t)
{
    return -1;
}

void Link::onEvent(int events)
{
    switch (events)
    {
    case EPOLLIN:
    {
        handler.onDataReceived();
    }
    break;
    case EPOLLOUT:
    {
        epoll.mod(*this, EPOLLIN);
        handler.onConnected();
    }
    break;
    default:
    {
        close();
        handler.onError();
    }
    break;
    }
}

int Link::getFd() const
{
    return fd;
}

} // namespace reactor
