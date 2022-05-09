#pragma once

#include <vector>
#include <memory>

#include "Queue.hpp"
#include "EntityId.hpp"
#include "ReactorInterface.hpp"
#include "Logger.hpp"

namespace app::ua
{

template <typename ENTITY>
class UaEntityPool
{
    static constexpr unsigned capacity = 32;

public:
    template <typename...OTHERS>
    explicit UaEntityPool(const char* name_, OTHERS&...others)
        : name(name_)
        , ids(capacity)
    {
        pool.reserve(capacity);
        for (EntityId uid = 0; uid < capacity; ++uid)
        {
            pool.push_back(std::make_unique<ENTITY>(uid, others...));
            ids.push(uid);
        }
    }

    ~UaEntityPool() {}

    bool alloc(EntityId& uid)
    {
        if (ids.empty())
        {
            return false;
        }
        uid = ids.front();
        ids.pop();
        LM(UA, LD, "Alloc %s uid=%u", name, uid);
        return true;
    }

    void release(EntityId uid)
    {
        LM(UA, LD, "Release %s uid=%u", name, uid);
        ids.push(uid);
    }

    ENTITY& get(EntityId uid)
    {
        return *(pool[uid]);
    }

private:
    const char* name;
    std::vector<std::unique_ptr<ENTITY>> pool;
    app::Queue<EntityId> ids;
};

} // namespace app::ua
