#include "ModbusClientSend.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientBackoff.hpp"
#include "ModbusClientReceive.hpp"
#include "ModbusClientConnected.hpp"
#include "ModbusClient.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientSend::onEnter(ModbusClientFsm& fsm)
{
    fsm.getEntity().startTimer(ModbusClient::sendDelay);
}

void ModbusClientSend::onReceiveTransactionReq(ModbusClientFsm&)
{}

void ModbusClientSend::onDataReceived(ModbusClientFsm& fsm)
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
    default:
    {
        LM(MODBUS, LE, "Unexpected");
    }
    break;
    }
}

void ModbusClientSend::onTimer(ModbusClientFsm& fsm)
{
    switch (fsm.getEntity().send())
    {
    case Status::codecError:
    {
        fsm.getEntity().startTimer(ModbusClient::sendDelay);
    }
    break;
    case Status::error:
    {
        fsm.getEntity().provideRspError();
        fsm.getEntity().close();
        fsm.transit<ModbusClientBackoff>();
    }
    break;
    case Status::noerror:
    {
        fsm.transit<ModbusClientConnected>();
    }
    break;
    case Status::done:
    {
        fsm.transit<ModbusClientReceive>();
    }
    break;
    }
}

void ModbusClientSend::onExit(ModbusClientFsm& fsm)
{
    fsm.getEntity().stopTimer();
}

} // namespace app::modbus
