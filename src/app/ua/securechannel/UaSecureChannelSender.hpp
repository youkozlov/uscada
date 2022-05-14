#pragma once

#include "SenderBase.hpp"

#include "MsgUaSecureChannelInitRsp.hpp"
#include "MsgUaSecureChannelConfigRsp.hpp"
#include "MsgUaOpenSecureChannelRsp.hpp"
#include "MsgUaCloseSecureChannelRsp.hpp"
#include "MsgUaSecuredMessageSendReq.hpp"
#include "MsgUaConnectionReleaseReq.hpp"
#include "MsgUaEncodedMessageReceiveInd.hpp"
#include "MsgUaSecureChannelReleaseRsp.hpp"

namespace app::ua::securechannel
{

class Sender : public reactor::SenderBase<Sender>
{
public:
    virtual ~Sender() {}

    virtual void send(MsgUaSecureChannelInitRsp const&) = 0;
    virtual void send(MsgUaSecureChannelConfigRsp const&) = 0;
    virtual void send(MsgUaOpenSecureChannelRsp const&) = 0;
    virtual void send(MsgUaCloseSecureChannelRsp const&) = 0;
    virtual void send(MsgUaSecuredMessageSendReq const&) = 0;
    virtual void send(MsgUaConnectionReleaseReq const&) = 0;
    virtual void send(MsgUaEncodedMessageReceiveInd const&) = 0;
    virtual void send(MsgUaSecureChannelReleaseRsp const&) = 0;
};

} // namespace app::ua::securechannel
