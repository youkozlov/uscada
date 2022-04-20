#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusClientAduReq : public reactor::MsgBase<ModbusClientAduReq, CompIds::modbus, MsgIds::modbusClientAduReq>
{
};

} // namespace app
