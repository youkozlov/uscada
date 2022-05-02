#pragma once

#include "FileDescriptorInterface.hpp"
#include "TimerHandler.hpp"
#include "TimerInterface.hpp"

namespace app::reactor
{

class EpollInterface;

class Timer : public FileDescriptorInterface, public TimerInterface
{
public:
    explicit Timer(EpollInterface&);

    ~Timer();

    void create();

    void close();

    void setHandler(TimerHandler);

private:

    void start(long) final;

    void stop() final;

    int fileDescriptor() const final;

    void setFileDescriptor(int) final {}

    void onFileDescriptorEvent(int) final;

    void release() final;

    EpollInterface& epoll;
    TimerHandler handler;
    int fd;
};


} // namespace app::reactor
