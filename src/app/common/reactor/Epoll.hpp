#pragma once

#include <sys/epoll.h>

#include "EpollInterface.hpp"

namespace app::reactor
{

class FileDescriptorInterface;

class Epoll : public EpollInterface
{
public:
    explicit Epoll(unsigned);

    ~Epoll();

    void wait();

private:

    unsigned const id;

    int add(FileDescriptorInterface&, int) final;

    int mod(FileDescriptorInterface&, int) final;

    int del(FileDescriptorInterface&) final;

    static constexpr int MAX_EVENTS = 10;
    static constexpr int DEFAULT_TIMEOUT = 1000;

    int epollfd;
};

} // namespace app::reactor
