#include "MsgMemStorage.hpp"
#include <cstdlib>
#include <cstring>

namespace reactor
{

MsgMemStorage::MsgMemStorage(std::size_t chunkSize_, std::size_t numChunks_)
    : chunkSize(chunkSize_)
    , numChunks(numChunks_)
{
    auto const totalMem = chunkSize * numChunks;

    mem = ::malloc(totalMem + 15);

    ptr = (void*)(((uintptr_t)mem + 15) & ~(uintptr_t)0x0F);

    for (std::size_t i = 0; i < numChunks; ++i)
    {
        freeIds.push(i);
    }
}

MsgMemStorage::~MsgMemStorage()
{
    ::free(mem);
}

bool MsgMemStorage::push(const void* data, std::uint64_t len)
{
    std::lock_guard<std::mutex> guard(mutex);

    if (freeIds.empty())
    {
        return false;
    }
    unsigned id = freeIds.front();
    freeIds.pop();
    busyIds.push(id);
    Item& item = *static_cast<Item*>(get(id));
    item.len = len;
    std::memcpy(item.data, data, len);
    return true;
}

bool MsgMemStorage::pop(void* data)
{
    std::lock_guard<std::mutex> guard(mutex);

    if (busyIds.empty())
    {
        return false;
    }
    unsigned id = busyIds.front();
    busyIds.pop();
    freeIds.push(id);
    Item& item = *static_cast<Item*>(get(id));
    std::memcpy(data, item.data, item.len);
    return true;
}

void* MsgMemStorage::get(unsigned id)
{
    return (void*)((uintptr_t)ptr + chunkSize * id);
}

} // namespace reactor
