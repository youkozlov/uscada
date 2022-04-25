#include "ModbusTestInit.hpp"
#include "ModbusTestFsm.hpp"
#include "ModbusTestController.hpp"
#include "ModbusTestConfigure.hpp"

namespace app::controller
{

void ModbusTestInit::onEnter(ModbusTestFsm& fsm)
{
    fsm.getEntity().sendModbusReleaseReq();
}

void ModbusTestInit::onStart(ModbusTestFsm& fsm)
{
    fsm.getEntity().sendModbusInitReq();
}

void ModbusTestInit::onStop(ModbusTestFsm& fsm)
{
    fsm.getEntity().sendModbusReleaseReq();
}

void ModbusTestInit::onModbusInitRspReceive(ModbusTestFsm& fsm, ModbusInitRsp const& rsp)
{
    fsm.getEntity().process(rsp);
    fsm.transit<ModbusTestConfigure>();
}

void ModbusTestInit::onModbusReleaseRspReceive(ModbusTestFsm& fsm, ModbusReleaseRsp const& rsp)
{
    fsm.getEntity().process(rsp);
}

} // namespace app::controller
