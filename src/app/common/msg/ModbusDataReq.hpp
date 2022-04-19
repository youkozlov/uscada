#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusDataReq : public reactor::MsgBase<ModbusDataReq, CompIds::modbus, MsgIds::modbusDataReq>
{
};

} // namespace app
