#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusReleaseReq : public reactor::MsgBase<ModbusReleaseReq, CompIds::compModbus, MsgIds::modbusReleaseReq>
{
};

} // namespace app
