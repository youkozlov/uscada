#include "Epoll.hpp"

#include <unistd.h>
#include <stdexcept>

#include <iostream>

#include "FdHandler.hpp"

namespace reactor
{

Epoll::Epoll()
{
    epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        throw std::runtime_error("epoll_create1");
    }
}

Epoll::~Epoll()
{
    close(epollfd);
}

void Epoll::add(FdHandler& handler, int events)
{
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = &handler;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, handler.getFd(), &ev) == -1)
    {
        throw std::runtime_error("epoll_ctl: add fd");
    }
}

void Epoll::mod(FdHandler& handler, int events)
{
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = &handler;
    if (epoll_ctl(epollfd, EPOLL_CTL_MOD, handler.getFd(), &ev) == -1)
    {
        throw std::runtime_error("epoll_ctl: add fd");
    }
}

void Epoll::del(FdHandler& handler)
{
    struct epoll_event ev;
    ev.events = 0;
    ev.data.ptr = &handler;
    if (epoll_ctl(epollfd, EPOLL_CTL_DEL, handler.getFd(), &ev) == -1)
    {
        throw std::runtime_error("epoll_ctl: add fd");
    }
}

void Epoll::wait()
{
    struct epoll_event events[MAX_EVENTS];

    int nfds = epoll_wait(epollfd, events, MAX_EVENTS, DEFAULT_TIMEOUT);
    if (nfds == -1)
    {
        throw std::runtime_error("epoll_wait");
    }

    for (int n = 0; n < nfds; ++n)
    {
        if (events[n].data.ptr == nullptr)
        {
            throw std::runtime_error("invalid ptr");
        }
        FdHandler& handler = *static_cast<FdHandler*>(events[n].data.ptr);
        handler.onEvent(events[n].events);
    }
}

} // namespace reactor
