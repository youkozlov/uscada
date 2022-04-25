#include "ModbusTestFsm.hpp"
#include "ModbusTestInit.hpp"
#include "ModbusTestController.hpp"

namespace app::controller
{

ModbusTestFsm::ModbusTestFsm(ModbusTestController& entity_)
    : state(&getSingleton<ModbusTestInit>())
    , entity(entity_)
{
}

ModbusTestFsm::~ModbusTestFsm()
{
}

ModbusTestState& ModbusTestFsm::getState()
{
    return *state;
}

ModbusTestController& ModbusTestFsm::getEntity()
{
    return entity;
}

} // namespace app::controller
