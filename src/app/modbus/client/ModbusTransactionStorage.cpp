#include "ModbusTransactionStorage.hpp"

#include <cstring>

#include "Logger.hpp"

namespace app::modbus
{

ModbusTransactionStorage::ModbusTransactionStorage()
    : pool(capacity)
{
    for (unsigned id = 0; id < capacity; ++id)
    {
        freeIds.push(id);
    }
}

ModbusTransactionStorage::~ModbusTransactionStorage()
{
}

bool ModbusTransactionStorage::push(ModbusTransaction const& tr)
{
    if (freeIds.empty())
    {
        return false;
    }
    unsigned const id = freeIds.front();
    pool[id] = tr;
    if (tr.numBytes > transactionNumBytes)
    {
        LM(MODBUS, LE, "Invalid numer of bytes, %u", tr.numBytes);
        return false;
    }
    if (tr.data && tr.numBytes)
    {
        char* dst = &buffer[0] + transactionNumBytes * id;
        std::memcpy(dst, tr.data, tr.numBytes);
        pool[id].data = dst;
    }
    busyIds.push(id);
    freeIds.pop();
    return true;
}

ModbusTransaction const& ModbusTransactionStorage::front()
{
    if (busyIds.empty())
    {
        LM(MODBUS, LE, "Storage is empty");
    }
    return pool[busyIds.front()];
}

void ModbusTransactionStorage::pop()
{
    if (busyIds.empty())
    {
        LM(MODBUS, LE, "Storage is empty");
        return;
    }
    freeIds.push(busyIds.front());
    busyIds.pop();
}

bool ModbusTransactionStorage::empty() const
{
    return busyIds.empty();
}

} // namespace app::modbus
