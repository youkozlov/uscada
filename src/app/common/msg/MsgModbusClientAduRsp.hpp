#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "EntityId.hpp"
#include "TransactId.hpp"
#include "ModbusError.hpp"
#include "MsgStatus.hpp"

namespace app
{

struct MsgModbusClientAduRsp : public reactor::MsgBase<MsgModbusClientAduRsp, CompIds::compController, MsgIds::modbusClientAduRsp>
{
    EntityId        clientId;
    TransactId      transactId;
    ModbusError     error;
    MsgStatus       status;
    uint16_t        numBytes;
    uint8_t         data[];

    std::size_t size() const final
    {
        return sizeof(MsgModbusClientAduRsp) + numBytes;
    }
};

} // namespace app
