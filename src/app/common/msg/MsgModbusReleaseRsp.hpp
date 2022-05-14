#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgModbusReleaseRsp : public reactor::MsgBase<MsgModbusReleaseRsp, CompIds::compController, MsgIds::modbusReleaseRsp>
{
};

} // namespace app
