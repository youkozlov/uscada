#include "Epoll.hpp"

#include <unistd.h>
#include <stdexcept>

#include <iostream>

#include "FileDescriptorInterface.hpp"
#include "Logger.hpp"

namespace app::reactor
{

Epoll::Epoll(unsigned id_)
    : id(id_)
{
    epollfd = ::epoll_create1(0);
    if (epollfd == -1)
    {
        throw std::runtime_error("epoll_create1");
    }
}

Epoll::~Epoll()
{
    ::close(epollfd);
}

int Epoll::add(FileDescriptorInterface& fd, int events)
{
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = &fd;
    return ::epoll_ctl(epollfd, EPOLL_CTL_ADD, fd.fileDescriptor(), &ev);
}

int Epoll::mod(FileDescriptorInterface& fd, int events)
{
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = &fd;
    return ::epoll_ctl(epollfd, EPOLL_CTL_MOD, fd.fileDescriptor(), &ev);
}

int Epoll::del(FileDescriptorInterface& fd)
{
    struct epoll_event ev;
    ev.events = 0;
    ev.data.ptr = &fd;
    return ::epoll_ctl(epollfd, EPOLL_CTL_DEL, fd.fileDescriptor(), &ev);
}

void Epoll::wait()
{
    struct epoll_event events[MAX_EVENTS];

    int nfds = ::epoll_wait(epollfd, events, MAX_EVENTS, DEFAULT_TIMEOUT);
    if (nfds == -1)
    {
        LM(GEN, LE, "epoll_wait errno: %d", errno);
        throw std::runtime_error("epoll_wait");
    }

    for (int n = 0; n < nfds; ++n)
    {
        if (events[n].data.ptr == nullptr)
        {
            throw std::runtime_error("invalid ptr");
        }
        FileDescriptorInterface& fd = *static_cast<FileDescriptorInterface*>(events[n].data.ptr);
        fd.onFileDescriptorEvent(events[n].events);
    }
}

} // namespace app::reactor
