#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusReleaseRsp : public reactor::MsgBase<ModbusReleaseRsp, CompIds::compController, MsgIds::modbusReleaseRsp>
{
};

} // namespace app
