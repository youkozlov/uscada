#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "EntityId.hpp"
#include "ModbusFunc.hpp"


namespace app
{

struct ModbusAduReq : public reactor::MsgBase<ModbusAduReq, CompIds::controller, MsgIds::modbusAduReq>
{
    EntityId   serverId;
    EntityId   sessionId;
    EntityId   aduId;
    ModbusFunc func;
    uint16_t   start;
    uint16_t   numItems;
    uint16_t   items[];
};

} // namespace app
