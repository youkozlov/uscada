#pragma once 

#include "MsgId.hpp"
#include "MsgHandler.hpp"
#include "TimerId.hpp"
#include "TimerHandler.hpp"
#include "PipeEvent.hpp"
#include "TimerInterface.hpp"
#include "LinkHandler.hpp"
#include "LinkInterface.hpp"

namespace reactor
{

class ReactorInterface
{
public:
    virtual ~ReactorInterface() {}

    virtual void registerHandler(MsgId, MsgHandler) = 0;

    virtual TimerInterface* createTimer(TimerHandler) = 0;

    virtual LinkInterface* createLink(LinkHandler&) = 0;

    virtual void send(MsgInterface const&) = 0;

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual void run() = 0;

    virtual void handlePipeEvent(PipeEvent const&) = 0;
};

}