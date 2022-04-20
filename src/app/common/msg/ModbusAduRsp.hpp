#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "EntityId.hpp"
#include "MsgStatus.hpp"

namespace app
{

struct ModbusAduRsp : public reactor::MsgBase<ModbusAduRsp, CompIds::modbus, MsgIds::modbusAduRsp>
{
    EntityId  serverId;
    EntityId  sessionId;
    EntityId  aduId;
    MsgStatus status;
    uint16_t  numItems;
    uint16_t  items[];
};

} // namespace app
