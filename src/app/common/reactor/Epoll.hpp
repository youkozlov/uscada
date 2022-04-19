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

    void add(FdHandler&, int events);

    void mod(FdHandler&, int events);

    void del(FdHandler&);

    void wait();

private:
    static constexpr int MAX_EVENTS = 10;
    static constexpr int DEFAULT_TIMEOUT = 10;

    int epollfd;
};

} // namespace reactor
