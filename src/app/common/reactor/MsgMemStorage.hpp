#pragma once

#include <cstdint>
#include <mutex>

#include "Queue.hpp"

namespace app::reactor
{

class MsgMemStorage
{
public:
    MsgMemStorage(std::size_t, std::size_t);

    ~MsgMemStorage();

    bool push(const void*, std::uint64_t);

    bool pop(void*);

private:
    struct Item
    {
        std::uint64_t len;
        char data[];
    };
    void* get(unsigned);

    std::size_t const chunkSize;
    std::size_t const numChunks;

    std::mutex mutex;
    void* mem;
    void* ptr;
    app::Queue<unsigned> freeIds;
    app::Queue<unsigned> busyIds;
};

} // namespace app::reactor
