#include "ModbusClientBackoff.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientConnect.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientBackoff::onEnter(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onEnter");

    fsm.startTimer();
}

void ModbusClientBackoff::onTimer(ModbusClientFsm& fsm)
{
    fsm.transit<ModbusClientConnect>();
}

void ModbusClientBackoff::onExit(ModbusClientFsm& fsm)
{
    fsm.stopTimer();
}

} // namespace app::modbus
