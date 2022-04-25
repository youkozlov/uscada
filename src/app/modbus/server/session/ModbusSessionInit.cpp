#include "ModbusSessionInit.hpp"
#include "ModbusSessionFsm.hpp"
#include "ModbusSession.hpp"
#include "ModbusSessionConnected.hpp"

namespace app::modbus
{

void ModbusSessionInit::onEnter(ModbusSessionFsm& fsm)
{
    fsm.getEntity().releaseSession();
}

void ModbusSessionInit::onStart(ModbusSessionFsm& fsm)
{
    fsm.transit<ModbusSessionConnected>();
}

} // namespace app::modbus
