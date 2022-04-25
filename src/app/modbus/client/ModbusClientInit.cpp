#include "ModbusClientInit.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientConnect.hpp"
#include "ModbusClient.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientInit::onStart(ModbusClientFsm& fsm)
{
    fsm.transit<ModbusClientConnect>();
}

void ModbusClientInit::onReceiveTransactionReq(ModbusClientFsm& fsm)
{
    fsm.getEntity().provideRspError();
}

} // namespace app::modbus
