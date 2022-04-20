#pragma once

#include <map>
#include <vector>
#include <memory>
#include <atomic>

#include "ReactorInterface.hpp"
#include "ThreadHandler.hpp"
#include "PipeHandler.hpp"


namespace reactor
{

class Pipe;
class Epoll;
class Thread;
class MsgMemPool;

class Reactor : public ReactorInterface, public ThreadHandler, public PipeHandler
{
public:
    struct Init
    {
        std::size_t numThreads;
        uint64_t cpuMask;
        MsgMemPool& msgMemPool;
    };
    
    explicit Reactor(Init const&);

    ~Reactor();

    void registerHandler(MsgId, MsgHandler) final;

    TimerPtr createTimer(TimerHandler) final;

    LinkPtr createLink(LinkHandler&) final;

    AcceptorPtr createAcceptor(AcceptorHandler&) final;

    void send(MsgInterface const&) final;

    void start() final;

    void stop() final;

    void run() final;

    void onPipeEvent(PipeEvent const&) final;

private:
    std::atomic<bool> stopped;
    MsgMemPool& msgMemPool;
    std::unique_ptr<Epoll> epoll;
    std::unique_ptr<Pipe> pipe;
    std::vector<std::unique_ptr<Thread>> threads;
    std::map<MsgId, MsgHandler> handlers;
};

} // namespace reactor
