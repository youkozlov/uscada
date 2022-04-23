#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusInitReq : public reactor::MsgBase<ModbusInitReq, CompIds::compModbus, MsgIds::modbusInitReq>
{
    unsigned maxNumServers;
    unsigned maxNumClients;
};

} // namespace app
