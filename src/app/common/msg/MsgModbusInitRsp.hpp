#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgModbusInitRsp : public reactor::MsgBase<MsgModbusInitRsp, CompIds::compController, MsgIds::modbusInitRsp>
{
};

} // namespace app
