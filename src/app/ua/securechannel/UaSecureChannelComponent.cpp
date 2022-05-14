#include "UaSecureChannelComponent.hpp"
#include "UaSecureChannel.hpp"

#include "Logger.hpp"

namespace app::ua::securechannel
{

UaSecureChannelComponent::UaSecureChannelComponent(reactor::SenderInterface& sender_, reactor::ReactorInterface& reactor_)
    : ComponentBase(sender_, reactor_)
    , sender(*this)
    , reactor(reactor_)
{
    registerComponent();
}

void UaSecureChannelComponent::registerComponent()
{
    getReactor().registerHandlers
    ({
          { MsgUaSecureChannelInitReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaSecureChannelInitReq const&>(msg)); }}
        , { MsgUaSecureChannelConfigReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaSecureChannelConfigReq const&>(msg)); }}
        , { MsgUaOpenSecureChannelReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaOpenSecureChannelReq const&>(msg)); } }
        , { MsgUaCloseSecureChannelReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaCloseSecureChannelReq const&>(msg)); } }
        , { MsgUaAssociateSecureChannelReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaAssociateSecureChannelReq const&>(msg)); } }
        , { MsgUaSecuredMessageReceiveInd::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaSecuredMessageReceiveInd const&>(msg)); } }
        , { MsgUaConnectionReleaseInd::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaConnectionReleaseInd const&>(msg)); } }
        , { MsgUaEncodedMessageSendReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaEncodedMessageSendReq const&>(msg)); } }
        , { MsgUaSecureChannelReleaseReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaSecureChannelReleaseReq const&>(msg)); }}
    });
}

void UaSecureChannelComponent::receive(MsgUaSecureChannelInitReq const&)
{
    LM(UASC, LD, "UaSecureChannelInitReq received");

    secureChannel = std::make_unique<UaSecureChannel>();

    reactor::MsgStore<MsgUaSecureChannelInitRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void UaSecureChannelComponent::receive(MsgUaSecureChannelReleaseReq const&)
{
    LM(UASC, LD, "UaSecureChannelReleaseReq received");

    secureChannel.reset();

    reactor::MsgStore<MsgUaSecureChannelReleaseRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void UaSecureChannelComponent::receive(MsgUaSecureChannelConfigReq const& req)
{
    LM(UASC, LD, "UaSecureChannelConfigReq received");

    if (secureChannel)
        secureChannel->receive(req);
}

void UaSecureChannelComponent::receive(MsgUaOpenSecureChannelReq const& req)
{
    LM(UASC, LD, "UaOpenSecureChannelReq received");

    if (secureChannel)
        secureChannel->receive(req);
}

void UaSecureChannelComponent::receive(MsgUaCloseSecureChannelReq const& req)
{
    LM(UASC, LD, "UaCloseSecureChannelReq received");

    if (secureChannel)
        secureChannel->receive(req);
}

void UaSecureChannelComponent::receive(MsgUaAssociateSecureChannelReq const& req)
{
    LM(UASC, LD, "UaAssociateSecureChannelReq received");

    if (secureChannel)
        secureChannel->receive(req);
}

void UaSecureChannelComponent::receive(MsgUaSecuredMessageReceiveInd const& req)
{
    LM(UASC, LD, "UaSecuredMessageReceiveInd received");

    if (secureChannel)
        secureChannel->receive(req);
}

void UaSecureChannelComponent::receive(MsgUaEncodedMessageSendReq const& req)
{
    LM(UASC, LD, "UaEncodedMessageSendReq received");

    if (secureChannel)
        secureChannel->receive(req);
}

void UaSecureChannelComponent::receive(MsgUaConnectionReleaseInd const& rsp)
{
    LM(UASC, LD, "UaConnectionReleaseInd received");
    if (secureChannel)
        secureChannel->receive(rsp);
}

} // namespace app::ua::securechannel
