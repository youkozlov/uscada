#include "UaServerSecureChannelEstablished.hpp"
#include "UaServerSecureChannelInit.hpp"
#include "UaServerSecureChannel.hpp"

namespace app::ua::securechannel
{

void UaServerSecureChannelEstablished::onReceive(UaServerSecureChannel& fsm, MsgUaCloseSecureChannelReq const& msg)
{
    fsm.receive(msg);
    fsm.sendUaConnectionReleaseReq(msg.connectionId);
    fsm.transit<UaServerSecureChannelInit>();
}

void UaServerSecureChannelEstablished::onReceive(UaServerSecureChannel& fsm, MsgUaAssociateSecureChannelReq const& msg)
{
    fsm.receive(msg);
}

void UaServerSecureChannelEstablished::onReceive(UaServerSecureChannel& fsm, MsgUaConnectionReleaseInd const&)
{
    fsm.transit<UaServerSecureChannelInit>();
}

void UaServerSecureChannelEstablished::onReceive(UaServerSecureChannel& fsm, MsgUaEncodedMessageSendReq const& msg)
{
    fsm.receive(msg);
}

void UaServerSecureChannelEstablished::onReceive(UaServerSecureChannel& fsm, MsgUaSecuredMessageReceiveInd const& msg)
{
    if (UaServerSecureChannel::Result::done != fsm.receive(msg))
    {
        fsm.sendUaConnectionReleaseReq(msg.connectionId);
        fsm.transit<UaServerSecureChannelInit>();
    }
}

} // namespace app::ua::securechannel
