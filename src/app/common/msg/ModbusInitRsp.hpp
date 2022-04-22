#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusInitRsp : public reactor::MsgBase<ModbusInitRsp, CompIds::compController, MsgIds::modbusInitRsp>
{
};

} // namespace app
