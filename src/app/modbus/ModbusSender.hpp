#pragma once

#include "SenderBase.hpp"

#include "ModbusInitRsp.hpp"
#include "ModbusConfigRsp.hpp"
#include "ModbusAduReq.hpp"
#include "ModbusReleaseRsp.hpp"

namespace app::modbus
{

class Sender : public reactor::SenderBase<Sender>
{
public:
    virtual ~Sender() {}

    virtual void send(ModbusInitRsp const&) = 0;
    virtual void send(ModbusConfigRsp const&) = 0;
    virtual void send(ModbusAduReq const&) = 0;
    virtual void send(ModbusReleaseRsp const&) = 0;
};

} // namespace app::modbus
