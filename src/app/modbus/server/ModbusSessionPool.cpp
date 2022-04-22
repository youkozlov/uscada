#include "ModbusSessionPool.hpp"
#include "ModbusSession.hpp"

namespace app::modbus
{

ModbusSessionPool::ModbusSessionPool(ModbusSessionHandler& handler)
{
    for (int id = 0; id < capacity; ++id)
    {
        sessions.push_back(std::make_unique<ModbusSession>(handler, id));
        ids.push(id);
    }
}

ModbusSessionPool::~ModbusSessionPool()
{
}

bool ModbusSessionPool::alloc(int& id)
{
    if (ids.empty())
    {
        return false;
    }
    id = ids.front();
    ids.pop();
    return true;
}

void ModbusSessionPool::free(int id)
{
    ids.push(id);
}

ModbusSession& ModbusSessionPool::get(int id) const
{
    return *sessions[id];
}
} // namespace app::modbus
