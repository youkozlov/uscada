#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgModbusInitReq : public reactor::MsgBase<MsgModbusInitReq, CompIds::compModbus, MsgIds::modbusInitReq>
{
    unsigned maxNumServers;
    unsigned maxNumClients;
};

} // namespace app
