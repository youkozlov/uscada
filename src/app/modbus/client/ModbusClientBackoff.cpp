#include "ModbusClientBackoff.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientConnect.hpp"
#include "ModbusClient.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientBackoff::onEnter(ModbusClientFsm& fsm)
{
    fsm.getEntity().startTimer(ModbusClient::backoffTimeout);
}

void ModbusClientBackoff::onReceiveTransactionReq(ModbusClientFsm& fsm)
{
    fsm.getEntity().provideRspError();
}

void ModbusClientBackoff::onTimer(ModbusClientFsm& fsm)
{
    fsm.transit<ModbusClientConnect>();
}

void ModbusClientBackoff::onExit(ModbusClientFsm& fsm)
{
    fsm.getEntity().stopTimer();
}

} // namespace app::modbus
