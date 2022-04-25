#include "ModbusAduStorage.hpp"

#include <cstring>

#include "Logger.hpp"

namespace app::modbus
{

ModbusAduStorage::ModbusAduStorage()
    : freeIds(capacity)
    , busyIds(capacity)
    , adus(capacity)
{
    for (unsigned id = 0; id < capacity; ++id)
    {
        freeIds.push(id);
    }
}

ModbusAduStorage::~ModbusAduStorage()
{
}

bool ModbusAduStorage::push(AduRequest const& adu)
{
    if (freeIds.empty())
    {
        LM(MODBUS, LE, "Storage is full");
        return false;
    }
    auto const& id = freeIds.front();
    adus[id] = adu;
    if (adu.numBytes > maxAduLen)
    {
        LM(MODBUS, LE, "Invalid number of bytes, %u", adu.numBytes);
        return false;
    }
    if (adu.data && adu.numBytes)
    {
        std::memcpy(&buffer[maxAduLen * id], adu.data, adu.numBytes);
        adus[id].data = &buffer[maxAduLen * id];
    }
    else
    {
        adus[id].data = nullptr;
    }
    busyIds.push(id);
    freeIds.pop();
    return true;
}

AduRequest const& ModbusAduStorage::front()
{
    if (busyIds.empty())
    {
        LM(MODBUS, LE, "Storage is empty");
    }
    return adus[busyIds.front()];
}

void ModbusAduStorage::pop()
{
    if (busyIds.empty())
    {
        LM(MODBUS, LE, "Storage is empty");
        return;
    }
    freeIds.push(busyIds.front());
    busyIds.pop();
}

bool ModbusAduStorage::empty() const
{
    return busyIds.empty();
}

} // namespace app::modbus
