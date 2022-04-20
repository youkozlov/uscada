#include "Link.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>

#include "Logger.hpp"

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
        close();
    }
}

void Link::assignFd(int val)
{
    if (-1 != fd)
    {
        throw std::runtime_error("already connected");
    }
    fd = val;
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
    if (-1 == epoll.add(*this, EPOLLIN | EPOLLET | EPOLLOUT))
    {
        ::close(fd);
        fd = -1;
        throw std::runtime_error("fd add");
    }
}

void Link::close()
{
    if (-1 == fd)
    {
        throw std::runtime_error("invalid fd");
    }
    LM(GEN, LD, "Close");
    if (-1 == epoll.del(*this))
    {
        LM(GEN, LE, "fd del errno: %d", errno);
    }
    if (-1 == ::close(fd))
    {
        LM(GEN, LE, "close errno: %d", errno);
    }
    fd = -1;
}

int Link::send(void const* data, std::size_t len)
{
    if (-1 == fd)
    {
        return -1;
    }
    if (-1 == ::write(fd, data, len))
    {
        return -1;
    }
    return 1;
}

int Link::receive(void* data, std::size_t len)
{
    return ::read(fd, data, len);
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
        if (-1 == epoll.mod(*this, EPOLLIN | EPOLLET))
        {
            LM(GEN, LD, "fd mod");
            close();
            handler.onError();
        }
        else
        {
            handler.onConnected();
        }
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
