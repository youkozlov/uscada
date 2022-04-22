#pragma once

#include <sys/epoll.h>

#include "EpollInterface.hpp"

namespace reactor
{

class FdHandler;

class Epoll : public EpollInterface
{
public:
    explicit Epoll();

    ~Epoll();

    void wait();

private:

    int add(FdHandler&, int) final;

    int mod(FdHandler&, int) final;

    int del(FdHandler&) final;

    static constexpr int MAX_EVENTS = 10;
    static constexpr int DEFAULT_TIMEOUT = 10;

    int epollfd;
};

} // namespace reactor
