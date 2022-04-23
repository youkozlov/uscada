#include "ModbusClientConnected.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientBackoff.hpp"
#include "ModbusClientReceive.hpp"
#include "ModbusClient.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientConnected::send(ModbusClientFsm& fsm)
{
    switch (fsm.getEntity().send())
    {
    case Status::error:
    {
        fsm.getEntity().provideRspError();
        fsm.getEntity().close();
        fsm.transit<ModbusClientBackoff>();
    }
    break;
    case Status::done:
    {
        fsm.transit<ModbusClientReceive>();
    }
    break;
    }
}

void ModbusClientConnected::onEnter(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onEnter");

    send(fsm);
}

void ModbusClientConnected::onReceiveTransactionReq(ModbusClientFsm& fsm)
{
    send(fsm);
}

void ModbusClientConnected::onDataReceived(ModbusClientFsm& fsm)
{
    switch (fsm.getEntity().receive())
    {
    case Status::error:
    {
        fsm.getEntity().close();
        fsm.transit<ModbusClientBackoff>();
    }
    break;
    default:
    {
        LM(MODBUS, LE, "onDataReceived unexpected");
    }
    break;
    }
}

void ModbusClientConnected::onError(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onError");

    fsm.getEntity().provideRspError();
    fsm.transit<ModbusClientBackoff>();
}

void ModbusClientConnected::onTimer(ModbusClientFsm& fsm)
{
}

void ModbusClientConnected::onExit(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onExit");
}

} // namespace app::modbus
