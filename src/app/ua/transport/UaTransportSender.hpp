#pragma once

#include "SenderBase.hpp"

#include "MsgUaTransportInitRsp.hpp"
#include "MsgUaTransportConfigRsp.hpp"
#include "MsgUaOpenSecureChannelReq.hpp"
#include "MsgUaCloseSecureChannelReq.hpp"
#include "MsgUaSecuredMessageReceiveInd.hpp"
#include "MsgUaConnectionReleaseInd.hpp"
#include "MsgUaTransportReleaseRsp.hpp"

namespace app::ua::transport
{

class Sender : public reactor::SenderBase<Sender>
{
public:
    virtual ~Sender() {}

    virtual void send(MsgUaTransportInitRsp const&) = 0;
    virtual void send(MsgUaTransportConfigRsp const&) = 0;
    virtual void send(MsgUaOpenSecureChannelReq const&) = 0;
    virtual void send(MsgUaCloseSecureChannelReq const&) = 0;
    virtual void send(MsgUaSecuredMessageReceiveInd const&) = 0;
    virtual void send(MsgUaConnectionReleaseInd const&) = 0;
    virtual void send(MsgUaTransportReleaseRsp const&) = 0;
};

} // namespace app::ua::transport
