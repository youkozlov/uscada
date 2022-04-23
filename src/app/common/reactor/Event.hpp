#pragma once

#include <cstdint>

#include "FdHandler.hpp"
namespace reactor
{

class EpollInterface;
class EventHandler;

class Event : public FdHandler
{
public:
    explicit Event(EpollInterface&, EventHandler&);

    ~Event();

    void send();

    int getFd() const final;

    void onEvent(int) final;

private:
    EpollInterface& epoll;
    EventHandler& handler;
    int fd;
};

} // namespace reactor
