#include "ModbusClientConnect.hpp"
#include "ModbusClientConnected.hpp"
#include "ModbusClientBackoff.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClient.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientConnect::onEnter(ModbusClientFsm& fsm)
{
    fsm.getEntity().startTimer(ModbusClient::connectTimeout);
    fsm.getEntity().connect();
}

void ModbusClientConnect::onReceiveTransactionReq(ModbusClientFsm& fsm)
{
    fsm.getEntity().provideRspError();
}

void ModbusClientConnect::onConnected(ModbusClientFsm& fsm)
{
    fsm.transit<ModbusClientConnected>();
}

void ModbusClientConnect::onError(ModbusClientFsm& fsm)
{
    fsm.transit<ModbusClientBackoff>();
}

void ModbusClientConnect::onTimer(ModbusClientFsm& fsm)
{
    fsm.getEntity().close();
    fsm.transit<ModbusClientBackoff>();
}

void ModbusClientConnect::onExit(ModbusClientFsm& fsm)
{
    fsm.getEntity().stopTimer();
}

} // namespace app::modbus
