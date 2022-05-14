#pragma once

#include "SenderBase.hpp"

#include "MsgModbusInitReq.hpp"
#include "MsgModbusReleaseReq.hpp"
#include "MsgModbusConfigReq.hpp"
#include "MsgModbusClientAduReq.hpp"
#include "MsgModbusAduRsp.hpp"
#include "MsgUaSecureChannelInitReq.hpp"
#include "MsgUaSecureChannelConfigReq.hpp"
#include "MsgUaSecureChannelReleaseReq.hpp"
#include "MsgUaTransportInitReq.hpp"
#include "MsgUaTransportConfigReq.hpp"
#include "MsgUaTransportReleaseReq.hpp"
#include "MsgUaServiceInitReq.hpp"
#include "MsgUaServiceConfigReq.hpp"
#include "MsgUaServiceReleaseReq.hpp"


namespace app::controller
{

class Sender : public reactor::SenderBase<Sender>
{
public:
    virtual ~Sender() {}

    virtual void send(MsgModbusInitReq const&) = 0;
    virtual void send(MsgModbusReleaseReq const&) = 0;
    virtual void send(MsgModbusConfigReq const&) = 0;
    virtual void send(MsgModbusClientAduReq const&) = 0;
    virtual void send(MsgModbusAduRsp const&) = 0;
    virtual void send(MsgUaSecureChannelInitReq const&) = 0;
    virtual void send(MsgUaSecureChannelConfigReq const&) = 0;
    virtual void send(MsgUaSecureChannelReleaseReq const&) = 0;
    virtual void send(MsgUaTransportInitReq const&) = 0;
    virtual void send(MsgUaTransportConfigReq const&) = 0;
    virtual void send(MsgUaTransportReleaseReq const&) = 0;
    virtual void send(MsgUaServiceInitReq const&) = 0;
    virtual void send(MsgUaServiceConfigReq const&) = 0;
    virtual void send(MsgUaServiceReleaseReq const&) = 0;
};

} // namespace app::modbus
