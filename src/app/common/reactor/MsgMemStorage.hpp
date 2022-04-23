#pragma once

#include <queue>
#include <cstdint>
#include <mutex>

namespace reactor
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
    std::queue<unsigned> freeIds;
    std::queue<unsigned> busyIds;
};

} // namespace reactor
