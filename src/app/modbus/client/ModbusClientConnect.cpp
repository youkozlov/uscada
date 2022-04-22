#include "ModbusClientConnect.hpp"
#include "ModbusClientSend.hpp"
#include "ModbusClientBackoff.hpp"
#include "ModbusClientFsm.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientConnect::onEnter(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onEnter");

    fsm.startTimer();
    fsm.connect();
}

void ModbusClientConnect::onConnected(ModbusClientFsm& fsm)
{
    fsm.transit<ModbusClientSend>();
}

void ModbusClientConnect::onError(ModbusClientFsm& fsm)
{
    fsm.transit<ModbusClientBackoff>();
}

void ModbusClientConnect::onTimer(ModbusClientFsm& fsm)
{
    fsm.close();
    fsm.transit<ModbusClientBackoff>();
}

void ModbusClientConnect::onExit(ModbusClientFsm& fsm)
{
    fsm.stopTimer();
}

} // namespace app::modbus
