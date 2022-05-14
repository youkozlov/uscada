#pragma once

#include "UaServerSecureChannelState.hpp"

namespace app::ua::securechannel
{

class UaServerSecureChannelEstablished : public UaServerSecureChannelState
{
public:
    UaServerSecureChannelEstablished() {}

    char const* name() const final { return "UaServerSecureChannelEstablished"; }

    void onReceive(UaServerSecureChannel&, MsgUaCloseSecureChannelReq const&) final;
    void onReceive(UaServerSecureChannel&, MsgUaAssociateSecureChannelReq const&) final;
    void onReceive(UaServerSecureChannel&, MsgUaConnectionReleaseInd const&) final;
    void onReceive(UaServerSecureChannel&, MsgUaSecuredMessageReceiveInd const&) final;
    void onReceive(UaServerSecureChannel&, MsgUaEncodedMessageSendReq const&) final;
};

} // namespace app::ua::securechannel
