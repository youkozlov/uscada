#include "ReactorSimple.hpp"

#include <stdexcept>
#include <cstring>
#include <iostream>

#include "Pipe.hpp"
#include "Epoll.hpp"
#include "Timer.hpp"
#include "Link.hpp"
#include "Thread.hpp"
#include "MsgMemPool.hpp"
#include "MsgInterface.hpp"

namespace reactor
{

ReactorSimple::ReactorSimple(Init const& init)
    : stopped(false)
    , msgMemPool(init.msgMemPool)
{
    if (0 == init.numThreads)
    {
        throw std::runtime_error("Unexpected number of threads");
    }

    pipe = std::make_unique<Pipe>(*this);

    epoll = std::make_unique<Epoll>();

    epoll->add(*pipe, EPOLLIN);

    for (size_t i = 0; i < init.numThreads; ++i)
    {
        threads.push_back(std::make_unique<Thread>(init.cpuMask));
    }
}

ReactorSimple::~ReactorSimple()
{
}

void ReactorSimple::registerHandler(MsgId id, MsgHandler hanler)
{
    handlers[id] = hanler;
}

TimerInterface* ReactorSimple::createTimer(TimerHandler handler)
{
    timers.push_back(std::make_unique<Timer>(handler));
    epoll->add(*timers.back(), EPOLLIN);
    return &*timers.back();
}

LinkInterface* ReactorSimple::createLink(LinkHandler& handler)
{
    links.push_back(std::make_unique<Link>(handler, *epoll));
    return &*links.back();
}

void ReactorSimple::send(MsgInterface const& msg)
{
    PipeEvent ev;
    if (not msgMemPool.alloc(ev.id))
    {
        return;
    }
    std::memcpy(msgMemPool.get(ev.id), &msg, msg.size());
    pipe->send(ev);
}

void ReactorSimple::start()
{
    for (auto& thread : threads)
    {
        thread->start(*this);
    }
}

void ReactorSimple::stop()
{
    PipeEvent ev;
    ev.id = -1;
    pipe->send(ev);
}

void ReactorSimple::handlePipeEvent(PipeEvent const& ev)
{
    if (stopped)
    {
        return;
    }
    if (ev.id == -1)
    {
        stopped = true;
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

void ReactorSimple::run()
{
    std::cout << "run enter" << std::endl;

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

    for (auto& timer : timers)
    {
        timer->release();
    }

    std::cout << "run exit" << std::endl;
}

} // namespace reactor
