#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "EntityId.hpp"
#include "MsgStatus.hpp"

namespace app
{

struct ModbusConfigStatus
{
    EntityId id;
    MsgStatus status;
};

struct ModbusConfigRsp : public reactor::MsgBase<ModbusConfigRsp, CompIds::compController, MsgIds::modbusConfigRsp>
{
    unsigned numItems;
    ModbusConfigStatus items[];

    std::size_t size() const final
    {
        return sizeof(ModbusConfigRsp) + sizeof(ModbusConfigStatus) * numItems;
    }
};

} // namespace app
