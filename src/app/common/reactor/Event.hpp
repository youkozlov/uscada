#pragma once

#include <cstdint>

#include "FileDescriptorInterface.hpp"
namespace app::reactor
{

class EpollInterface;
class EventHandler;

class Event : public FileDescriptorInterface
{
public:
    explicit Event(EpollInterface&, EventHandler&);

    ~Event();

    void send();

private:
    int fileDescriptor() const final;

    void setFileDescriptor(int) final {}

    void onFileDescriptorEvent(int) final;

    EpollInterface& epoll;
    EventHandler& handler;
    int fd;
};

} // namespace app::reactor
