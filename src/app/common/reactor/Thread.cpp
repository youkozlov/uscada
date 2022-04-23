#include "Thread.hpp"
#include "ThreadHandler.hpp"
#include "Logger.hpp"

#include <iostream>
#include <stdexcept>

namespace reactor
{

namespace
{

static void* executer(void* args)
{
    ThreadHandler& handler = *static_cast<ThreadHandler*>(args);
    handler.run();
    return nullptr;
}

}

Thread::Thread(uint64_t cpuMask_, ThreadHandler& handler_)
    : cpuMask(cpuMask_)
    , handler(handler_)
{
    int result = pthread_attr_init(&attr);
    if (result != 0)
    {
        throw std::runtime_error("pthread_attr_init");
    }
}

Thread::~Thread()
{
    int result = pthread_attr_destroy(&attr);
    if (result != 0)
    {
        LM(GEN, LE, "pthread_attr_destroy");
    }

    result = pthread_join(tid, nullptr);
    if (result != 0)
    {
        LM(GEN, LE, "pthread_join");
    }
}

void Thread::start()
{
    int policy = SCHED_FIFO;
    int result = ::pthread_attr_setschedpolicy(&attr, policy);
    if (result != 0)
    {
        throw std::runtime_error("pthread_attr_setschedpolicy");
    }

    result = pthread_create(&tid, &attr, &executer, &handler);
    if (result != 0)
    {
        throw std::runtime_error("pthread_create");
    }

    if (0 == cpuMask)
    {
        return;
    }

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);

    for (int j = 0; j < 64; ++j)
    {
        if ((cpuMask >> j) & 0x1)
        {
            CPU_SET(j, &cpuset);
        }
    }

    result = pthread_setaffinity_np(tid, sizeof(cpuset), &cpuset);
    if (result != 0)
    {
        throw std::runtime_error("pthread_setaffinity_np");
    }

    cpu_set_t cpuget;
    CPU_ZERO(&cpuget);

    result = pthread_getaffinity_np(tid, sizeof(cpuget), &cpuget);
    if (result != 0)
    {
        throw std::runtime_error("pthread_getaffinity_np");
    }

    if (CPU_EQUAL(&cpuget, &cpuset) == 0)
    {
        throw std::runtime_error("pthread_getaffinity_np result is not match with cpuset");
    }
}

} // namespace reactor
