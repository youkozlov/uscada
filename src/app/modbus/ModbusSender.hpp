#pragma once

#include "SenderBase.hpp"

#include "MsgModbusInitRsp.hpp"
#include "MsgModbusConfigRsp.hpp"
#include "MsgModbusAduReq.hpp"
#include "MsgModbusClientAduRsp.hpp"
#include "MsgModbusReleaseRsp.hpp"

namespace app::modbus
{

class Sender : public reactor::SenderBase<Sender>
{
public:
    virtual ~Sender() {}

    virtual void send(MsgModbusInitRsp const&) = 0;
    virtual void send(MsgModbusConfigRsp const&) = 0;
    virtual void send(MsgModbusAduReq const&) = 0;
    virtual void send(MsgModbusClientAduRsp const&) = 0;
    virtual void send(MsgModbusReleaseRsp const&) = 0;
};

} // namespace app::modbus
