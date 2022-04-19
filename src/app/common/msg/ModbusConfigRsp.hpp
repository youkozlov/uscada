#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusConfigRsp : public reactor::MsgBase<ModbusConfigRsp, CompIds::controller, MsgIds::modbusConfigRsp>
{
};

} // namespace app
