#include "ModbusTestConfigure.hpp"
#include "ModbusTestFsm.hpp"
#include "ModbusTestController.hpp"
#include "ModbusTestRun.hpp"

namespace app::controller
{

void ModbusTestConfigure::onEnter(ModbusTestFsm& fsm)
{
    fsm.getEntity().sendModbusConfigReq();
}

void ModbusTestConfigure::onModbusConfigRspReceive(ModbusTestFsm& fsm, ModbusConfigRsp const& rsp)
{
    fsm.getEntity().process(rsp);
    fsm.transit<ModbusTestRun>();
}

} // namespace app::controller
