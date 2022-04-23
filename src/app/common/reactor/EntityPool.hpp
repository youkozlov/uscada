#pragma once

#include <vector>
#include <queue>
#include <memory>

#include "EpollInterface.hpp"
#include "Logger.hpp"

namespace reactor
{

template <typename ENTITY>
class EntityPool
{
public:
    explicit EntityPool(EpollInterface& epoll, const char* name_, unsigned capacity = 32)
        : name(name_)
    {
        for (unsigned uid = 0; uid < capacity; ++uid)
        {
            pool.push_back(std::make_unique<ENTITY>(epoll));
            ids.push(uid);
        }
    }

    ~EntityPool() {}

    bool alloc(unsigned& uid)
    {
        if (ids.empty())
        {
            return false;
        }
        uid = ids.front();
        ids.pop();
        LM(CTRL, LD, "Alloc %s uid=%u", name, uid);
        return true;
    }

    void release(unsigned uid)
    {
        LM(CTRL, LD, "Release %s uid=%u", name, uid);
        ids.push(uid);
    }

    ENTITY& get(unsigned uid)
    {
        return *(pool[uid]);
    }

private:
    const char* name;
    std::vector<std::unique_ptr<ENTITY>> pool;
    std::queue<unsigned> ids;
};

} // namespace reactor
