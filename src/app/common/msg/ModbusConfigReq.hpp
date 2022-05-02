#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"
#include "LinkAddr.hpp"
#include "EntityId.hpp"

namespace app
{

struct ModbusConfig
{
    enum class Mode
    {
          server
        , client
    };
    EntityId id;
    Mode     mode;
    reactor::LinkAddr addr;
};

struct ModbusConfigReq : public reactor::MsgBase<ModbusConfigReq, CompIds::compModbus, MsgIds::modbusConfigReq>
{
    unsigned numItems;
    ModbusConfig items[];

    std::size_t size() const final
    {
        return sizeof(ModbusConfigReq) + sizeof(ModbusConfig) * numItems;
    }
};

} // namespace app
