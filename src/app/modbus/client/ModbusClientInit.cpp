#include "ModbusClientInit.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientConnect.hpp"
#include "ModbusClient.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientInit::onStart(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "onStart");

    fsm.transit<ModbusClientConnect>();
}

void ModbusClientInit::onReceiveTransactionReq(ModbusClientFsm& fsm)
{
    fsm.getEntity().provideRspError();
}

} // namespace app::modbus
