#pragma once

#include <cstdint>
#include <pthread.h>
#include <functional>

namespace app::reactor
{

class ThreadHandler;

class Thread
{
public:
    explicit Thread(uint64_t, ThreadHandler&);

    ~Thread();

    void start();

private:
    uint64_t const cpuMask;
    ThreadHandler& handler;
    pthread_t tid;
    pthread_attr_t attr;
};

} // namespace app::reactor
