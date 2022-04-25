#include "ModbusTestSetup.hpp"
#include "ModbusTestFsm.hpp"
#include "ModbusTestController.hpp"
#include "ModbusTestInit.hpp"
#include "ModbusTestRun.hpp"

namespace app::controller
{

void ModbusTestSetup::onEnter(ModbusTestFsm& fsm)
{
    fsm.getEntity().startTimer(ModbusTestController::runDelay);
}

void ModbusTestSetup::onTimer(ModbusTestFsm& fsm)
{
    fsm.transit<ModbusTestRun>();
}

void ModbusTestSetup::onStop(ModbusTestFsm& fsm)
{
    fsm.transit<ModbusTestInit>();
}

void ModbusTestSetup::onExit(ModbusTestFsm& fsm)
{
    fsm.getEntity().stopTimer();
}

} // namespace app::controller
