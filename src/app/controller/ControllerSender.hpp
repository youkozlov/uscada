#pragma once

#include "SenderBase.hpp"

#include "ModbusInitReq.hpp"
#include "ModbusReleaseReq.hpp"
#include "ModbusConfigReq.hpp"
#include "ModbusClientAduReq.hpp"
#include "ModbusAduRsp.hpp"

namespace app::controller
{

class Sender : public reactor::SenderBase<Sender>
{
public:
    virtual ~Sender() {}

    virtual void send(ModbusInitReq const&) = 0;
    virtual void send(ModbusReleaseReq const&) = 0;
    virtual void send(ModbusConfigReq const&) = 0;
    virtual void send(ModbusClientAduReq const&) = 0;
    virtual void send(ModbusAduRsp const&) = 0;
};

} // namespace app::modbus
