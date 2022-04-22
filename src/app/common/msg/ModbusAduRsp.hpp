#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "EntityId.hpp"
#include "MsgStatus.hpp"

namespace app
{

struct ModbusAduRsp : public reactor::MsgBase<ModbusAduRsp, CompIds::compModbus, MsgIds::modbusAduRsp>
{
    EntityId  serverId;
    EntityId  sessionId;
    EntityId  aduId;
    MsgStatus status;
    uint16_t  numBytes;
    uint8_t   data[];

    std::size_t size() const final
    {
        return sizeof(ModbusAduRsp) + numBytes;
    }
};



} // namespace app
