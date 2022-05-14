#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "EntityId.hpp"
#include "ModbusError.hpp"
#include "MsgStatus.hpp"

namespace app
{

struct MsgModbusAduRsp : public reactor::MsgBase<MsgModbusAduRsp, CompIds::compModbus, MsgIds::modbusAduRsp>
{
    EntityId  serverId;
    EntityId  sessionId;
    uint16_t  transactId;
    ModbusError error;
    MsgStatus status;
    uint16_t  numBytes;
    uint8_t   data[];

    std::size_t size() const final
    {
        return sizeof(MsgModbusAduRsp) + numBytes;
    }
};



} // namespace app
