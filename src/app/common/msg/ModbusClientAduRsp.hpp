#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusClientAduRsp : public reactor::MsgBase<ModbusClientAduRsp, CompIds::controller, MsgIds::modbusClientAduRsp>
{
};

} // namespace app
