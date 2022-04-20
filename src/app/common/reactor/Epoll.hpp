#pragma once

#include <functional>
#include <sys/epoll.h>

namespace reactor
{

class FdHandler;

class Epoll
{
public:
    explicit Epoll();

    ~Epoll();

    int add(FdHandler&, int events);

    int mod(FdHandler&, int events);

    int del(FdHandler&);

    void wait();

private:
    static constexpr int MAX_EVENTS = 10;
    static constexpr int DEFAULT_TIMEOUT = 10;

    int epollfd;
};

} // namespace reactor
