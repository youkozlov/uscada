#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "EntityId.hpp"
#include "ModbusFunc.hpp"


namespace app
{

struct ModbusAduReq : public reactor::MsgBase<ModbusAduReq, CompIds::compController, MsgIds::modbusAduReq>
{
    EntityId   serverId;
    EntityId   sessionId;
    EntityId   aduId;
    ModbusFunc func;
    uint16_t   startReg;
    uint16_t   numRegs;
    uint16_t   numBytes;
    uint8_t    data[];

    std::size_t size() const final
    {
        return sizeof(ModbusAduReq) + numBytes;
    }
};

} // namespace app
