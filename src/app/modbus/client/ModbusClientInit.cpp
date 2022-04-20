#include "ModbusClientInit.hpp"
#include "ModbusClientFsm.hpp"
#include "ModbusClientConnect.hpp"
#include "Logger.hpp"

namespace app
{

void ModbusClientInit::start(ModbusClientFsm& fsm)
{
    LM(MODBUS, LD, "Start");

    fsm.transit<ModbusClientConnect>();
}

} // namespace app
