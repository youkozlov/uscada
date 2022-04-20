#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusReleaseReq : public reactor::MsgBase<ModbusReleaseReq, CompIds::modbus, MsgIds::modbusReleaseReq>
{
};

} // namespace app
