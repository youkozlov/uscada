#include "Thread.hpp"
#include "ReactorInterface.hpp"

#include <iostream>
#include <stdexcept>

namespace reactor
{

namespace
{

static void* executer(void* args)
{
    ReactorInterface& reactor = *static_cast<ReactorInterface*>(args);
    reactor.run();
    return nullptr;
}

}

Thread::Thread(uint64_t cpuMask_)
    : cpuMask(cpuMask_)
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
        std::cout << "pthread_attr_destroy" << std::endl;
    }

    result = pthread_join(tid, nullptr);
    if (result != 0)
    {
        std::cout << "pthread_join" << std::endl;
    }
}

void Thread::start(ReactorInterface& reactor)
{
    int result = pthread_create(&tid, &attr, &executer, &reactor);
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
