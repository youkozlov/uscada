#include "ModbusSessionFsm.hpp"
#include "ModbusSessionInit.hpp"
#include "ModbusSession.hpp"

namespace app::modbus
{

ModbusSessionFsm::ModbusSessionFsm(ModbusSession& entity_)
    : state(&getSingleton<ModbusSessionInit>())
    , entity(entity_)
{
}

ModbusSessionFsm::~ModbusSessionFsm()
{
}

ModbusSessionState& ModbusSessionFsm::getState()
{
    return *state;
}

ModbusSession& ModbusSessionFsm::getEntity()
{
    return entity;
}

} // namespace app::modbus
