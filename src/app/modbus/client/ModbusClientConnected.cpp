#include "ModbusClientConnected.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientBackoff.hpp"
#include "ModbusClientSend.hpp"
#include "ModbusClient.hpp"
#include "Logger.hpp"

namespace app::modbus
{

void ModbusClientConnected::onReceiveTransactionReq(ModbusClientFsm& fsm)
{
    fsm.transit<ModbusClientSend>();
}

void ModbusClientConnected::onDataReceived(ModbusClientFsm& fsm)
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

} // namespace app::modbus
