#include "Link.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <sys/epoll.h>
#include "EpollInterface.hpp"

#include "Logger.hpp"

namespace app::reactor
{

Link::Link(EpollInterface& epoll_)
    : epoll(epoll_)
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

void Link::setFileDescriptor(int val)
{
    if (-1 != fd)
    {
        throw std::runtime_error("already connected");
    }
    fd = val;
}

void Link::connect(LinkAddr const& address)
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
    addr.sin_port = htons(ipv4port(address));
    addr.sin_addr.s_addr = htonl(ipv4addr(address));//INADDR_LOOPBACK
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
        LM(GEN, LI, "fd is closed");
        return;
    }
    LM(GEN, LD, "Close fd=%d", fd);
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

void Link::release()
{
    close();
    setHandler({});
}

int Link::send(void const* data, std::size_t len)
{
    if (-1 == fd)
    {
        return -1;
    }
    if (-1 == ::write(fd, data, len))
    {
        LM(GEN, LE, "write errno: %d", errno);
        return -1;
    }
    return 1;
}

LinkResult Link::receive(std::uint8_t* data, std::size_t len)
{
    if (-1 == fd)
    {
        return {LinkResult::error, 0};
    }
    int rc = ::read(fd, data, len);
    if (-1 == rc && EAGAIN == errno)
    {
        LM(GEN, LI, "Link(%d) read EAGAIN", fd);
        return {LinkResult::na, 0};
    }
    else if (-1 == rc)
    {
        LM(GEN, LI, "Link(%d) read rc: %d errno: %d", fd, rc, errno);
        return {LinkResult::error, 0};
    }
    return {LinkResult::ok, rc};
}

void Link::setHandler(LinkHandler val)
{
    handler = val;
}

void Link::onFileDescriptorEvent(int events)
{
    if (not handler)
    {
        LM(GEN, LE, "Handler is undefined");
        return;
    }
    switch (events)
    {
    case EPOLLIN:
    {
        handler(LinkEvent::data);
    }
    break;
    case EPOLLOUT:
    {
        if (-1 == epoll.mod(*this, EPOLLIN | EPOLLET))
        {
            LM(GEN, LE, "fd mod");
            close();
            handler(LinkEvent::error);
        }
        else
        {
            handler(LinkEvent::connected);
        }
    }
    break;
    default:
    {
        close();
        handler(LinkEvent::error);
    }
    break;
    }
}

int Link::fileDescriptor() const
{
    return fd;
}

} // namespace app::reactor
