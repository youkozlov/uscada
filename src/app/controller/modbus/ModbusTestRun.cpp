#include "ModbusTestRun.hpp"
#include "ModbusTestFsm.hpp"
#include "ModbusTestController.hpp"
#include "ModbusTestInit.hpp"
#include "ModbusTestSetup.hpp"

namespace app::controller
{

void ModbusTestRun::onEnter(ModbusTestFsm& fsm)
{
    fsm.getEntity().resetTestCaseCounter();
    fsm.getEntity().sendModbusClientAduReq();
}

void ModbusTestRun::onModbusClientAduRspReceive(ModbusTestFsm& fsm, ModbusClientAduRsp const& rsp)
{
    switch (fsm.getEntity().process(rsp))
    {
    case Result::noerror:
    {}
    break;
    case Result::done:
        fsm.transit<ModbusTestSetup>();
    break;
    case Result::error:
        fsm.transit<ModbusTestInit>();
    break;
    }
}

void ModbusTestRun::onModbusAduReqReceive(ModbusTestFsm& fsm, ModbusAduReq const& rsp)
{
    fsm.getEntity().process(rsp);
}

void ModbusTestRun::onStop(ModbusTestFsm& fsm)
{
    fsm.transit<ModbusTestInit>();
}

void ModbusTestRun::onExit(ModbusTestFsm&)
{
}

} // namespace app::controller
