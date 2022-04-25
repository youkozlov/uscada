#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "EntityId.hpp"
#include "ModbusFunction.hpp"


namespace app
{

struct ModbusAduReq : public reactor::MsgBase<ModbusAduReq, CompIds::compController, MsgIds::modbusAduReq>
{
    EntityId   serverId;
    EntityId   sessionId;
    uint16_t   transactId;
    ModbusFunction func;
    uint16_t   addr;
    uint16_t   startItem;
    uint16_t   numItems;
    uint16_t   numBytes;
    uint8_t    data[];

    std::size_t size() const final
    {
        return sizeof(ModbusAduReq) + numBytes;
    }
};

} // namespace app
