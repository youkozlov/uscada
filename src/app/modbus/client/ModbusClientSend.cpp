#include "ModbusClientSend.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientBackoff.hpp"
#include "ModbusClientReceive.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientSend::onEnter(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onEnter");
    fsm.startTimer();
}

void ModbusClientSend::onDataReceived(ModbusClientFsm& fsm)
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
        LM(MODBUS, LE, "onDataReceived unexpected call");
    }
    break;
    }
}

void ModbusClientSend::onTimer(ModbusClientFsm& fsm)
{
    switch (fsm.send())
    {
    case 0:
    {
        fsm.close();
        fsm.transit<ModbusClientBackoff>();
    }
    break;
    default:
    {
        fsm.transit<ModbusClientReceive>();
    }
    break;
    }
}

void ModbusClientSend::onExit(ModbusClientFsm& fsm)
{
    fsm.stopTimer();
}

} // namespace app::modbus
