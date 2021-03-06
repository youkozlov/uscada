#include "Acceptor.hpp"

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

Acceptor::Acceptor(EpollInterface& epoll_)
    : epoll(epoll_)
    , sfd(-1)
{
}

Acceptor::~Acceptor()
{
    if (-1 != sfd)
    {
        close();
    }
}

void Acceptor::setHandler(AcceptorHandler handler_)
{
    handler = handler_;
}

void Acceptor::release()
{
    close();
    setHandler({});
}

void Acceptor::listen(LinkAddr const& address)
{
    if (-1 != sfd)
    {
        throw std::runtime_error("already inused");
    }
    sfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sfd)
    {
        throw std::runtime_error("socket");
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(ipv4port(address));
    addr.sin_addr.s_addr = htonl(ipv4addr(address));
    if (-1 == ::bind(sfd, (struct sockaddr*) &addr, sizeof(addr)))
    {
        ::close(sfd);
        sfd = -1;
        throw std::runtime_error("bind");
    }

    int const LISTEN_BACKLOG = 10;

    if (-1 == ::listen(sfd, LISTEN_BACKLOG))
    {
        ::close(sfd);
        sfd = -1;
        throw std::runtime_error("listen");
    }

    if (-1 == epoll.add(*this, EPOLLIN))
    {
        ::close(sfd);
        sfd = -1;
        throw std::runtime_error("fd add");
    }
}

void Acceptor::close()
{
    if (-1 == sfd)
    {
        throw std::runtime_error("invalid sfd");
    }
    LM(GEN, LD, "Close");
    if (-1 == epoll.del(*this))
    {
        LM(GEN, LE, "fd del errno: %d", errno);
    }
    if (-1 == ::close(sfd))
    {
        LM(GEN, LE, "close errno: %d", errno);
    }
    sfd = -1;
}

int Acceptor::fileDescriptor() const
{
    return sfd;
}

void Acceptor::onFileDescriptorEvent(int)
{
    if (not handler)
    {
        LM(GEN, LW, "Handler is undefined");
        return;
    }
    handler();
}

void Acceptor::accept(LinkInterface& link)
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    int fd = ::accept(sfd, (struct sockaddr*)&addr, &addrlen);
    if (-1 == fd)
    {
        throw std::runtime_error("accept");
    }

    if (-1 == ::fcntl(fd, F_SETFL, O_NONBLOCK))
    {
        ::close(fd);
        throw std::runtime_error("fcntl");
    }

    link.setFileDescriptor(fd);

    if (-1 == epoll.add(link, EPOLLIN | EPOLLET))
    {
        ::close(fd);
        link.setFileDescriptor(-1);
        throw std::runtime_error("fd add");
    }
}

} // namespace app::reactor
