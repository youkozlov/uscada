#include "Reactor.hpp"

#include <stdexcept>
#include <cstring>
#include <iostream>

#include "Event.hpp"
#include "Epoll.hpp"
#include "Timer.hpp"
#include "Link.hpp"
#include "Acceptor.hpp"
#include "Thread.hpp"
#include "MsgMemStorage.hpp"
#include "MsgInterface.hpp"
#include "MaxMsgSize.hpp"
#include "Logger.hpp"

namespace reactor
{

Reactor::Reactor(Init const& init)
    : stopped(false)
    , msgMemStorage(std::make_unique<MsgMemStorage>(maxMsgSize, 128))
    , epoll(std::make_unique<Epoll>(init.id))
    , event(std::make_unique<Event>(*epoll, *this))
    , acceptorPool(*epoll, "acceptor")
    , linkPool(*epoll, "link")
    , timerPool(*epoll, "timer")
{
    if (0 == init.numThreads)
    {
        throw std::runtime_error("Unexpected number of threads");
    }
    for (size_t i = 0; i < init.numThreads; ++i)
    {
        threads.push_back(std::make_unique<Thread>(init.cpuMask, *this));
    }
}

Reactor::~Reactor()
{
}

void Reactor::registerHandler(MsgId id, MsgHandler handler)
{
    handlers[id] = handler;
}

void Reactor::registerHandlers(MsgHandlerVector const& handlerVector)
{
    for (auto& it : handlerVector)
    {
        handlers[std::get<MsgId>(it)] = std::get<MsgHandler>(it);
    }
}

TimerPtr Reactor::createTimer(TimerHandler* handler)
{
    unsigned uid;
    if (not timerPool.alloc(uid))
    {
        throw std::runtime_error("timerPool alloc");
    }
    Timer& timer = timerPool.get(uid);
    timer.create();
    timer.setHandler(handler);
    TimerPtr timerPtr(&timer, [this, uid](auto* timer)
    {
        timer->release();
        timerPool.release(uid);
    });
    return timerPtr;
}

LinkPtr Reactor::createLink(LinkHandler* handler)
{
    unsigned uid;
    if (not linkPool.alloc(uid))
    {
        throw std::runtime_error("linkPool alloc");
    }
    Link& link = linkPool.get(uid);
    link.setHandler(handler);
    LinkPtr linkPtr(&link, [this, uid](auto* link)
    {
        link->release();
        linkPool.release(uid);
    });
    return linkPtr;
}

AcceptorPtr Reactor::createAcceptor(AcceptorHandler* handler)
{
    unsigned uid;
    if (not acceptorPool.alloc(uid))
    {
        throw std::runtime_error("acceptorPool alloc");
    }
    Acceptor& acceptor = acceptorPool.get(uid);
    acceptor.setHandler(handler);
    AcceptorPtr acceptorPtr(&acceptor, [this, uid](auto* acceptor)
    {
        acceptor->release();
        acceptorPool.release(uid);
    });
    return acceptorPtr;
}

void Reactor::send(MsgInterface const& msg)
{
    if (not msgMemStorage->push(&msg, msg.size()))
    {
        LM(CTRL, LE, "Can not push msg");
        return;
    }
    LM(GEN, LD, "Send msgId=%zu", msg.getMsgId());
    event->send();
}

void Reactor::start()
{
    for (auto& thread : threads)
    {
        thread->start();
    }
}

void Reactor::stop()
{
    stopped = true;
}

void Reactor::onFdEvent(uint64_t val)
{
    if (stopped)
    {
        return;
    }

    for (uint64_t ev = 0; ev < val; ++ev)
    {
        alignas(64) char localBuf[maxMsgSize];
        if (not msgMemStorage->pop(&localBuf[0]))
        {
            LM(GEN, LE, "Mem storage is empty");
            return;
        }

        MsgInterface const& msg = *reinterpret_cast<MsgInterface const*>(&localBuf[0]);

        LM(GEN, LD, "Receive msgId=%zu", msg.getMsgId());

        MsgHandler& handler = handlers[msg.getMsgId()];
        if (handler)
        {
            handler(msg);
        }
        else
        {
            LM(GEN, LE, "Can not find handler: msgId=%zu", msg.getMsgId());
        }
    }
}

void Reactor::run()
{
    while (not stopped)
    {
        try
        {
            epoll->wait();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

} // namespace reactor
