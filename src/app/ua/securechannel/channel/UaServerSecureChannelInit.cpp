#include "UaServerSecureChannelInit.hpp"
#include "UaServerSecureChannelEstablished.hpp"
#include "UaServerSecureChannel.hpp"

namespace app::ua::securechannel
{

void UaServerSecureChannelInit::onEnter(UaServerSecureChannel& fsm)
{
    fsm.release();
}

void UaServerSecureChannelInit::onReceive(UaServerSecureChannel& fsm, MsgUaOpenSecureChannelReq const& msg)
{
    if (UaServerSecureChannel::Result::done == fsm.receive(msg))
    {
        fsm.transit<UaServerSecureChannelEstablished>();
    }
    else
    {
        fsm.sendUaConnectionReleaseReq(msg.connectionId);
        fsm.release();
    }
}

} // namespace app::ua::securechannel
