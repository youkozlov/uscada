#include "ModbusSessionConnected.hpp"
#include "ModbusSessionFsm.hpp"
#include "ModbusSessionInit.hpp"
#include "ModbusSessionWaitModbusAduRsp.hpp"
#include "ModbusSession.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusSessionConnected::onEnter(ModbusSessionFsm& fsm)
{
    fsm.getEntity().startTimer(ModbusSession::inactiveTimeout);
    fsm.getEntity().receivePreaction();
}

void ModbusSessionConnected::onDataReceived(ModbusSessionFsm& fsm)
{
    switch (fsm.getEntity().receive())
    {
    case Result::error:
    {
        fsm.transit<ModbusSessionInit>();
    }
    break;
    case Result::done:
    {
        fsm.transit<ModbusSessionWaitModbusAduRsp>();
    }
    break;
    case Result::noerror:
    {
    }
    break;
    default:
    {
        LM(MODBUS, LE, "Unexpected");
    }
    break;
    }
}

void ModbusSessionConnected::onTimer(ModbusSessionFsm& fsm)
{
    fsm.transit<ModbusSessionInit>();
}

void ModbusSessionConnected::onExit(ModbusSessionFsm& fsm)
{
    fsm.getEntity().stopTimer();
}

} // namespace app::modbus
