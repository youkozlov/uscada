#pragma once

#include <cstdint>
#include <pthread.h>
#include <functional>

namespace reactor
{

class ReactorInterface;

class Thread
{
public:
    explicit Thread(uint64_t);

    ~Thread();

    void start(ReactorInterface&);

private:

    uint64_t const cpuMask;
    pthread_t tid;
    pthread_attr_t attr;
};

} // namespace reactor
