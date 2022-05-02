#pragma once 

#include "MsgId.hpp"
#include "MsgHandler.hpp"
#include "MsgHandlerVector.hpp"
#include "TimerHandler.hpp"
#include "TimerPtr.hpp"
#include "LinkPtr.hpp"
#include "LinkHandler.hpp"
#include "AcceptorPtr.hpp"
#include "AcceptorHandler.hpp"

namespace reactor
{

class ReactorInterface
{
public:
    virtual ~ReactorInterface() {}

    virtual void registerHandler(MsgId, MsgHandler) = 0;

    virtual void registerHandlers(MsgHandlerVector const&) = 0;

    virtual TimerPtr createTimer(TimerHandler) = 0;

    virtual LinkPtr createLink(LinkHandler) = 0;

    virtual AcceptorPtr createAcceptor(AcceptorHandler*) = 0;

    virtual void send(MsgInterface const&) = 0;

    virtual void start() = 0;

    virtual void stop() = 0;
};

}