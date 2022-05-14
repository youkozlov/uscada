#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"
#include "EntityId.hpp"
#include "TransactId.hpp"
#include "ModbusFunction.hpp"
#include "MemUtils.hpp"

namespace app
{

struct ModbusClientAduReqItem
{
    EntityId        clientId;
    TransactId      transactId;
    ModbusFunction  func;
    uint16_t        addr;
    uint16_t        startItem;
    uint16_t        numItems;
    uint16_t        numBytes;
    uint8_t         data[];
};

struct MsgModbusClientAduReq : public reactor::MsgBase<MsgModbusClientAduReq, CompIds::compModbus, MsgIds::modbusClientAduReq>
{
    uint16_t                numItems;
    ModbusClientAduReqItem  items[];

    std::size_t size() const final
    {
        std::size_t msgSize = sizeof(MsgModbusClientAduReq);
        uintptr_t ptr = (uintptr_t)&items[0];
        for (uint16_t i = 0; i < numItems; ++i)
        {
            ModbusClientAduReqItem const& item = *reinterpret_cast<ModbusClientAduReqItem const*>(ptr);
            std::size_t const itemSize = sizeof(ModbusClientAduReqItem) + item.numBytes;
            std::size_t const itemAlignedSize = utils::memAlign(itemSize);
            ptr += itemAlignedSize;
            msgSize += itemAlignedSize;
        }
        return msgSize;
    }

    ModbusClientAduReqItem& item(uint16_t itemIdx)
    {
        uintptr_t ptr = (uintptr_t)&items[0];
        for (uint16_t i = 0; i < itemIdx; ++i)
        {
            ModbusClientAduReqItem& item = *reinterpret_cast<ModbusClientAduReqItem*>(ptr);
            std::size_t const itemSize = sizeof(ModbusClientAduReqItem) + item.numBytes;
            ptr += utils::memAlign(itemSize);
        }
        return *reinterpret_cast<ModbusClientAduReqItem*>(ptr);
    }

    ModbusClientAduReqItem const& item(uint16_t itemIdx) const
    {
        uintptr_t ptr = (uintptr_t)&items[0];
        for (uint16_t i = 0; i < itemIdx; ++i)
        {
            ModbusClientAduReqItem const& item = *reinterpret_cast<ModbusClientAduReqItem const*>(ptr);
            std::size_t const itemSize = sizeof(ModbusClientAduReqItem) + item.numBytes;
            ptr += utils::memAlign(itemSize);
        }
        return *reinterpret_cast<ModbusClientAduReqItem const*>(ptr);
    }
};

} // namespace app
