#pragma once

#include <queue>
#include <cstdint>
#include <mutex>

namespace reactor
{

class MsgMemPool
{
public:
    MsgMemPool(std::size_t, std::size_t);

    ~MsgMemPool();

    bool alloc(int&);

    void free(int);

    void* get(int);

private:
    std::size_t const chunkSize;
    std::size_t const numChunks;

    std::mutex mutex;
    void* mem;
    void* ptr;
    std::queue<int> ids;
};

} // namespace reactor
