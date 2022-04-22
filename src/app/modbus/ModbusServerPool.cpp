#include "ModbusServerPool.hpp"
#include "ModbusServer.hpp"


namespace app::modbus
{

ModbusServerPool::ModbusServerPool(ModbusSessionHandler& handler)
    : pool(capacity)
{
    for (int id = 0; id < capacity; ++id)
    {
        ids.push(id);
    }
}

ModbusServerPool::~ModbusServerPool()
{
}

bool ModbusServerPool::alloc(int& id)
{
    if (ids.empty())
    {
        return false;
    }
    id = ids.front();
    ids.pop();
    return true;
}

void ModbusServerPool::free(int id)
{
    ids.push(id);
}

ModbusServer& ModbusServerPool::get(int id) const
{
    return *sessions[id];
}

} // namespace app::modbus
