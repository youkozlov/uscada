#include "ModbusClientReceive.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientBackoff.hpp"
#include "ModbusClientSend.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientReceive::onEnter(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onEnter");

    fsm.startTimer();
}

void ModbusClientReceive::onDataReceived(ModbusClientFsm& fsm)
{
    switch (fsm.receive())
    {
    case 0:
    {
        fsm.close();
        fsm.transit<ModbusClientBackoff>();
    }
    break;
    default:
    {
        LM(MODBUS, LD, "Adu received");

        fsm.transit<ModbusClientSend>();
    }
    break;
    }
}

void ModbusClientReceive::onError(ModbusClientFsm& fsm)
{
    fsm.transit<ModbusClientBackoff>();
}

void ModbusClientReceive::onTimer(ModbusClientFsm& fsm)
{
    fsm.transit<ModbusClientSend>();
}

void ModbusClientReceive::onExit(ModbusClientFsm& fsm)
{
    fsm.stopTimer();
}

} // namespace app::modbus
