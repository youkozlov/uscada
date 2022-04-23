#include "ModbusSessionPool.hpp"
#include "Logger.hpp"

namespace app::modbus
{

ModbusSessionPool::ModbusSessionPool(ModbusSessionHandler& handler, unsigned capacity)
{
    for (ModbusSession::Uid uid = 0; uid < capacity; ++uid)
    {
        sessions.push_back(std::make_unique<ModbusSession>(handler, uid));
        ids.push(uid);
    }
}

ModbusSessionPool::~ModbusSessionPool()
{
}

bool ModbusSessionPool::alloc(ModbusSession::Uid& uid)
{
    if (ids.empty())
    {
        return false;
    }
    uid = ids.front();
    LM(MODBUS, LD, "Alloc session-%u", uid);
    ids.pop();
    return true;
}

void ModbusSessionPool::free(ModbusSession::Uid uid)
{
    LM(MODBUS, LD, "Release session-%u", uid);
    ids.push(uid);
}

ModbusSession& ModbusSessionPool::get(ModbusSession::Uid uid) const
{
    return *sessions[uid];
}
} // namespace app::modbus
