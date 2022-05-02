#pragma once

#include <map>
#include <vector>
#include <memory>
#include <atomic>

#include "ReactorInterface.hpp"
#include "ThreadHandler.hpp"
#include "EventHandler.hpp"
#include "EntityPool.hpp"
#include "Link.hpp"
#include "Timer.hpp"
#include "Acceptor.hpp"

namespace app::reactor
{

class Event;
class Epoll;
class Thread;
class MsgMemStorage;

class Reactor : public ReactorInterface, public ThreadHandler, public EventHandler
{
public:
    struct Init
    {
        unsigned id;
        std::size_t numThreads;
        uint64_t cpuMask;
    };
    
    explicit Reactor(Init const&);

    ~Reactor();

    void registerHandler(MsgId, MsgHandler) final;

    void registerHandlers(MsgHandlerVector const&) final;

    TimerPtr createTimer(TimerHandler) final;

    LinkPtr createLink(LinkHandler) final;

    AcceptorPtr createAcceptor(AcceptorHandler*) final;

    void send(MsgInterface const&) final;

    void start() final;

    void stop() final;

    void run() final;

    void onFdEvent(uint64_t) final;

private:
    void releaseLink(unsigned, LinkInterface*);

    std::atomic<bool> stopped;
    std::unique_ptr<MsgMemStorage> msgMemStorage;
    std::unique_ptr<Epoll> epoll;
    std::unique_ptr<Event> event;
    std::vector<std::unique_ptr<Thread>> threads;
    EntityPool<Acceptor> acceptorPool;
    EntityPool<Link> linkPool;
    EntityPool<Timer> timerPool;
    std::map<MsgId, MsgHandler> handlers;
};

} // namespace app::reactor
