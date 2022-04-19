#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusDataInd : public reactor::MsgBase<ModbusDataInd, CompIds::controller, MsgIds::modbusDataInd>
{
};

} // namespace app
