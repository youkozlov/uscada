#pragma once

#include <sys/epoll.h>

#include "EpollInterface.hpp"

namespace reactor
{

class FdHandler;

class Epoll : public EpollInterface
{
public:
    explicit Epoll(unsigned);

    ~Epoll();

    void wait();

private:

    unsigned const id;

    int add(FdHandler&, int) final;

    int mod(FdHandler&, int) final;

    int del(FdHandler&) final;

    static constexpr int MAX_EVENTS = 10;
    static constexpr int DEFAULT_TIMEOUT = 1000;

    int epollfd;
};

} // namespace reactor
