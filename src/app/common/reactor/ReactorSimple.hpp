#pragma once

#include <map>
#include <vector>
#include <memory>
#include <atomic>

#include "ReactorInterface.hpp"

namespace reactor
{

class Pipe;
class Epoll;
class Thread;
class Timer;
class Link;
class MsgMemPool;

class ReactorSimple : public ReactorInterface
{
public:
    struct Init
    {
        std::size_t numThreads;
        uint64_t cpuMask;
        MsgMemPool& msgMemPool;
    };
    
    explicit ReactorSimple(Init const&);

    ~ReactorSimple();

    void registerHandler(MsgId, MsgHandler) final;

    TimerInterface* createTimer(TimerHandler) final;

    LinkInterface* createLink(LinkHandler&) final;

    void send(MsgInterface const&) final;

    void start() final;

    void stop() final;

    void run() final;

    void handlePipeEvent(PipeEvent const&) final;

private:
    std::atomic<bool> stopped;
    MsgMemPool& msgMemPool;
    std::unique_ptr<Pipe> pipe;
    std::unique_ptr<Epoll> epoll;
    std::vector<std::unique_ptr<Link>> links;
    std::vector<std::unique_ptr<Timer>> timers;
    std::vector<std::unique_ptr<Thread>> threads;
    std::map<MsgId, MsgHandler> handlers;
};

} // namespace reactor
