#include "ModbusClientReceive.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientBackoff.hpp"
#include "ModbusClientSend.hpp"
#include "ModbusClient.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientReceive::onEnter(ModbusClientFsm& fsm)
{
    fsm.getEntity().startTimer(ModbusClient::receiveTimeout);
    fsm.getEntity().receivePreaction();
}

void ModbusClientReceive::onReceiveTransactionReq(ModbusClientFsm&)
{}

void ModbusClientReceive::onDataReceived(ModbusClientFsm& fsm)
{
    switch (fsm.getEntity().receive())
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
        fsm.transit<ModbusClientSend>();
    }
    break;
    case Status::codecError:
    {
        LM(MODBUS, LE, "Unexpected");
    }
    break;
    case Status::noerror:
    {
    }
    break;
    }
}

void ModbusClientReceive::onTimer(ModbusClientFsm& fsm)
{
    LM(MODBUS, LI, "onTimer");
    fsm.getEntity().provideRspTimeout();
    fsm.transit<ModbusClientSend>();
}

void ModbusClientReceive::onExit(ModbusClientFsm& fsm)
{
    fsm.getEntity().stopTimer();
    fsm.getEntity().receivePostaction();
}

} // namespace app::modbus
