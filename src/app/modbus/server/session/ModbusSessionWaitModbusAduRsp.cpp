#include "ModbusSessionWaitModbusAduRsp.hpp"
#include "ModbusSessionFsm.hpp"
#include "ModbusSessionConnected.hpp"
#include "ModbusSessionInit.hpp"
#include "ModbusSession.hpp"

namespace app::modbus
{

void ModbusSessionWaitModbusAduRsp::onEnter(ModbusSessionFsm& fsm)
{
    fsm.getEntity().startTimer(ModbusSession::aduRspTimeout);
}

void ModbusSessionWaitModbusAduRsp::onDataReceived(ModbusSessionFsm& fsm)
{
    switch (fsm.getEntity().receive())
    {
    case Result::error:
    {
        fsm.transit<ModbusSessionInit>();
    }
    break;
    default:
    {
        LM(MODBUS, LE, "Unexpected");
    }
    break;
    }
}

void ModbusSessionWaitModbusAduRsp::onModbusAduRspReceive(ModbusSessionFsm& fsm, ModbusAduRsp const& rsp)
{
    switch (fsm.getEntity().send(rsp))
    {
    case Result::error:
    {
        fsm.transit<ModbusSessionInit>();
    }
    break;
    case Result::done:
    {
        fsm.transit<ModbusSessionConnected>();
    }
    break;
    default:
    {
        LM(MODBUS, LE, "Unexpected");
    }
    break;
    }
}

void ModbusSessionWaitModbusAduRsp::onTimer(ModbusSessionFsm& fsm)
{
    LM(MODBUS, LE, "onTimer");
    fsm.transit<ModbusSessionConnected>();
}

void ModbusSessionWaitModbusAduRsp::onExit(ModbusSessionFsm& fsm)
{
    fsm.getEntity().stopTimer();
}

} // namespace app::modbus
