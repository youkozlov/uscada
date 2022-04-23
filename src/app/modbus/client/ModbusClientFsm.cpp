#include "ModbusClientFsm.hpp"
#include "ModbusClientInit.hpp"
#include "ModbusClient.hpp"

namespace app::modbus
{

ModbusClientFsm::ModbusClientFsm(ModbusClient& entity_)
    : state(&getSingleton<ModbusClientInit>())
    , entity(entity_)
{
}

ModbusClientFsm::~ModbusClientFsm()
{
}

ModbusClientState& ModbusClientFsm::getState()
{
    return *state;
}

ModbusClient& ModbusClientFsm::getEntity()
{
    return entity;
}

} // namespace app::modbus
