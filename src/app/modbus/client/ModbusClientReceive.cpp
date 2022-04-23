#include "ModbusClientReceive.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientBackoff.hpp"
#include "ModbusClientConnected.hpp"
#include "ModbusClient.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientReceive::onEnter(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onEnter");

    fsm.getEntity().startTimer(ModbusClient::receiveTimeout);
    fsm.getEntity().receivePrepare();
}

void ModbusClientReceive::onReceiveTransactionReq(ModbusClientFsm&)
{}

void ModbusClientReceive::onDataReceived(ModbusClientFsm& fsm)
{
    switch (fsm.getEntity().receive())
    {
    case Status::error:
    {
        fsm.getEntity().close();
        fsm.transit<ModbusClientBackoff>();
    }
    break;
    case Status::done:
    {
        fsm.transit<ModbusClientConnected>();
    }
    break;
    }
}

void ModbusClientReceive::onTimer(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onTimer");

    fsm.getEntity().provideRspTimeout();
    fsm.transit<ModbusClientConnected>();
}

void ModbusClientReceive::onExit(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onExit");

    fsm.getEntity().stopTimer();
}

} // namespace app::modbus
