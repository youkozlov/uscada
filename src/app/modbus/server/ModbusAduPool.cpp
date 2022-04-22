#include "ModbusAduPool.hpp"

namespace app::modbus
{

ModbusAduPool::ModbusAduPool()
    : adus(capacity)
{
    for (int id = 0; id < capacity; ++id)
    {
        ids.push(id);
    }
}

ModbusAduPool::~ModbusAduPool()
{
}

bool ModbusAduPool::alloc(int& id)
{
    if (ids.empty())
    {
        return false;
    }
    id = ids.front();
    ids.pop();
    return true;
}

void ModbusAduPool::free(int id)
{
    ids.push(id);
}

ModbusTcpAdu& ModbusAduPool::get(int id)
{
    return adus[id];
}

} // namespace app::modbus
