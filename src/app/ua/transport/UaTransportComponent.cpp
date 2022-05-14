#include "UaTransportComponent.hpp"
#include "UaTransport.hpp"

#include "Logger.hpp"

namespace app::ua::transport
{

UaTransportComponent::UaTransportComponent(reactor::SenderInterface& sender_, reactor::ReactorInterface& reactor_)
    : ComponentBase(sender_, reactor_)
    , sender(*this)
    , reactor(reactor_)
{
    registerComponent();
}

void UaTransportComponent::registerComponent()
{
    getReactor().registerHandlers
    ({
          { MsgUaTransportInitReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaTransportInitReq const&>(msg)); }}
        , { MsgUaTransportConfigReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaTransportConfigReq const&>(msg)); }}
        , { MsgUaOpenSecureChannelRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaOpenSecureChannelRsp const&>(msg)); } }
        , { MsgUaCloseSecureChannelRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaCloseSecureChannelRsp const&>(msg)); } }
        , { MsgUaSecuredMessageSendReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaSecuredMessageSendReq const&>(msg)); } }
        , { MsgUaConnectionReleaseReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaConnectionReleaseReq const&>(msg)); } }
        , { MsgUaTransportReleaseReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaTransportReleaseReq const&>(msg)); }}
    });
}

void UaTransportComponent::receive(MsgUaTransportInitReq const&)
{
    LM(UATL, LD, "UaTransportInitReq received");

    uaTransport = std::make_unique<UaTransport>();

    reactor::MsgStore<MsgUaTransportInitRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void UaTransportComponent::receive(MsgUaTransportReleaseReq const&)
{
    LM(UATL, LD, "UaTransportReleaseReq received");

    uaTransport.reset();

    reactor::MsgStore<MsgUaTransportReleaseRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void UaTransportComponent::receive(MsgUaTransportConfigReq const& req)
{
    LM(UATL, LD, "UaTransportConfigReq received");

    if (uaTransport)
        uaTransport->receive(req);
}

void UaTransportComponent::receive(MsgUaOpenSecureChannelRsp const& req)
{
    LM(UATL, LD, "UaOpenSecureChannelRsp received");

    if (uaTransport)
        uaTransport->receive(req);
}

void UaTransportComponent::receive(MsgUaCloseSecureChannelRsp const& req)
{
    LM(UATL, LD, "UaCloseSecureChannelRsp received");

    if (uaTransport)
        uaTransport->receive(req);
}


void UaTransportComponent::receive(MsgUaSecuredMessageSendReq const& req)
{
    LM(UATL, LD, "UaSecuredMessageSendReq received");

    if (uaTransport)
        uaTransport->receive(req);
}

void UaTransportComponent::receive(MsgUaConnectionReleaseReq const& rsp)
{
    LM(UATL, LD, "UaConnectionReleaseReq received");
    if (uaTransport)
        uaTransport->receive(rsp);
}

} // namespace app::ua::transport
