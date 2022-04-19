#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "LinkAddr.hpp"

namespace app
{

struct ModbusLinkConfig
{
    using Id = int;

    enum class Mode
    {
          server
        , client
    };

    Id id;
    Mode mode;
    reactor::LinkAddr addr;
};

struct ModbusConfigReq : public reactor::MsgBase<ModbusConfigReq, CompIds::modbus, MsgIds::modbusConfigReq>
{
    std::size_t numLinks;
    ModbusLinkConfig links[];
};

} // namespace app
