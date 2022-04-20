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
{
    if (0 == init.numThreads)
    {
        throw std::runtime_error("Unexpected number of threads");
    }

    epoll = std::make_unique<Epoll>();

    pipe = std::make_unique<Pipe>(*this, *epoll);

    for (size_t i = 0; i < init.numThreads; ++i)
    {
        threads.push_back(std::make_unique<Thread>(init.cpuMask, *this));
    }
}

Reactor::~Reactor()
{
}

void Reactor::registerHandler(MsgId id, MsgHandler hanler)
{
    handlers[id] = hanler;
}

TimerPtr Reactor::createTimer(TimerHandler handler)
{
    return std::make_unique<Timer>(handler, *epoll);
}

LinkPtr Reactor::createLink(LinkHandler& handler)
{
    return std::make_unique<Link>(handler, *epoll);
}

AcceptorPtr Reactor::createAcceptor(AcceptorHandler& handler)
{
    return std::make_unique<Acceptor>(handler, *epoll);
}

void Reactor::send(MsgInterface const& msg)
{
    PipeEvent ev;
    if (not msgMemPool.alloc(ev.id))
    {
        return;
    }
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
