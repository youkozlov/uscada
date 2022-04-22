#include "Reactor.hpp"

#include <stdexcept>
#include <cstring>
#include <iostream>

#include "Pipe.hpp"
#include "Epoll.hpp"
#include "Timer.hpp"
#include "Link.hpp"
#include "Acceptor.hpp"
#include "Thread.hpp"
#include "MsgMemPool.hpp"
#include "MsgInterface.hpp"
#include "Logger.hpp"

namespace reactor
{

Reactor::Reactor(Init const& init)
    : stopped(false)
    , msgMemPool(init.msgMemPool)
    , epoll(std::make_unique<Epoll>())
    , pipe(std::make_unique<Pipe>(*epoll, *this))
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

AcceptorPtr Reactor::createAcceptor(AcceptorHandler& handler)
{
    return std::make_unique<Acceptor>(*epoll, handler);
}

void Reactor::send(MsgInterface const& msg)
{
    PipeEvent ev;
    if (not msgMemPool.alloc(ev.id))
    {
        LM(CTRL, LE, "Can not alloc msg buffer");
        return;
    }
    LM(GEN, LD, "Send msgId=%zu size=%zu", msg.getMsgId(), msg.size());

    std::memcpy(msgMemPool.get(ev.id), &msg, msg.size());
    pipe->send(ev);
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

void Reactor::onPipeEvent(PipeEvent const& ev)
{
    if (stopped)
    {
        return;
    }
    MsgInterface const& msg = *static_cast<MsgInterface const*>(msgMemPool.get(ev.id));
    MsgHandler& handler = handlers[msg.getMsgId()];
    if (handler)
    {
        handler(msg);
    }
    else
    {
        LM(GEN, LE, "Can not find handler: msgId=%zu size=%zu", msg.getMsgId(), msg.size());
    }
    msgMemPool.free(ev.id);
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
