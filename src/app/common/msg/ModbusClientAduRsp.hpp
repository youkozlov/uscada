#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusClientAduRsp : public reactor::MsgBase<ModbusClientAduRsp, CompIds::compController, MsgIds::modbusClientAduRsp>
{
};

} // namespace app
