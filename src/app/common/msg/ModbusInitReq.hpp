#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusInitReq : public reactor::MsgBase<ModbusInitReq, CompIds::modbus, MsgIds::modbusInitReq>
{
};

} // namespace app
