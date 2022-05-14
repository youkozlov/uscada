#include "UaSecureChannel.hpp"
#include "UaSecureChannelReactor.hpp"
#include "Logger.hpp"

namespace app::ua::securechannel
{

UaSecureChannel::UaSecureChannel()
    : serverSecureChannelPool("UaServerSecureChannel", Reactor::get(), *this)
{
}

UaSecureChannel::~UaSecureChannel()
{
}

void UaSecureChannel::release(UaSecureChannelId uid)
{
    serverSecureChannelPool.release(uid);
}

void UaSecureChannel::receive(MsgUaSecureChannelConfigReq const&)
{
}

void UaSecureChannel::receive(MsgUaOpenSecureChannelReq const& msg)
{
    UaSecureChannelId uid;
    if (not serverSecureChannelPool.alloc(uid))
    {
        LM(UASC, LD, "Can not alloc channel");
        return;
    }
    auto& channel = serverSecureChannelPool.get(uid);
    channel.getState().onReceive(channel, msg);
}

void UaSecureChannel::receive(MsgUaCloseSecureChannelReq const& msg)
{
    auto& channel = serverSecureChannelPool.get(msg.secureChannelId);
    channel.getState().onReceive(channel, msg);
}

void UaSecureChannel::receive(MsgUaAssociateSecureChannelReq const& msg)
{
    auto& channel = serverSecureChannelPool.get(msg.hdr.secureChannelId);
    channel.getState().onReceive(channel, msg);
}

void UaSecureChannel::receive(MsgUaSecuredMessageReceiveInd const& msg)
{
    auto& channel = serverSecureChannelPool.get(msg.secureChannelId);
    channel.getState().onReceive(channel, msg);
}

void UaSecureChannel::receive(MsgUaEncodedMessageSendReq const& msg)
{
    auto& channel = serverSecureChannelPool.get(msg.hdr.secureChannelId);
    channel.getState().onReceive(channel, msg);
}

void UaSecureChannel::receive(MsgUaConnectionReleaseInd const& msg)
{
    auto& channel = serverSecureChannelPool.get(msg.secureChannelId);
    channel.getState().onReceive(channel, msg);
}

} // namespace app::ua::securechannel
