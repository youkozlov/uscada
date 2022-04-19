#include "MsgMemPool.hpp"
#include <cstdlib>

namespace reactor
{

MsgMemPool::MsgMemPool(std::size_t chunkSize_, std::size_t numChunks_)
    : chunkSize(chunkSize_)
    , numChunks(numChunks_)
{
    auto const totalMem = chunkSize * numChunks;

    mem = ::malloc(totalMem + 15);

    ptr = (void*)(((uintptr_t)mem + 15) & ~(uintptr_t)0x0F);

    for (std::size_t i = 0; i < numChunks; ++i)
    {
        ids.push(i);
    }
}

MsgMemPool::~MsgMemPool()
{
    ::free(mem);
}

bool MsgMemPool::alloc(int& id)
{
    std::lock_guard<std::mutex> guard(mutex);

    if (ids.empty())
    {
        return false;
    }
    id = ids.front();
    ids.pop();
    return true;
}

void MsgMemPool::free(int id)
{
    std::lock_guard<std::mutex> guard(mutex);

    ids.push(id);
}

void* MsgMemPool::get(int id)
{
    return (void*)((uintptr_t)ptr + chunkSize * id);
}

} // namespace reactor
