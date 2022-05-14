#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgModbusReleaseReq : public reactor::MsgBase<MsgModbusReleaseReq, CompIds::compModbus, MsgIds::modbusReleaseReq>
{
};

} // namespace app
