#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ModbusClientAduReq : public reactor::MsgBase<ModbusClientAduReq, CompIds::compModbus, MsgIds::modbusClientAduReq>
{
    EntityId   serverId;

    uint16_t   startReg;
    uint16_t   numRegs;
    uint16_t   numBytes;
    uint8_t    data[];

    std::size_t size() const final
    {
        return sizeof(ModbusClientAduReq) + numBytes;
    }
};

} // namespace app
