#include "UaServiceComponent.hpp"
#include "UaService.hpp"

#include "Logger.hpp"

namespace app::ua::service
{

UaServiceComponent::UaServiceComponent(reactor::SenderInterface& sender_, reactor::ReactorInterface& reactor_)
    : ComponentBase(sender_, reactor_)
    , sender(*this)
    , reactor(reactor_)
{
    registerComponent();
}

void UaServiceComponent::registerComponent()
{
    getReactor().registerHandlers
    ({
          { MsgUaServiceInitReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaServiceInitReq const&>(msg)); }}
        , { MsgUaServiceConfigReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaServiceConfigReq const&>(msg)); }}
        , { MsgUaEncodedMessageReceiveInd::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaEncodedMessageReceiveInd const&>(msg)); } }
        , { MsgUaServiceReleaseReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaServiceReleaseReq const&>(msg)); }}
    });
}

void UaServiceComponent::receive(MsgUaServiceInitReq const&)
{
    LM(UASRV, LD, "UaServiceInitReq received");

    service = std::make_unique<UaService>();

    reactor::MsgStore<MsgUaServiceInitRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void UaServiceComponent::receive(MsgUaServiceReleaseReq const&)
{
    LM(UASRV, LD, "UaServiceReleaseReq received");

    service.reset();

    reactor::MsgStore<MsgUaServiceReleaseRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void UaServiceComponent::receive(MsgUaServiceConfigReq const& req)
{
    LM(UASRV, LD, "UaServiceConfigReq received");

    if (service)
        service->receive(req);
}

void UaServiceComponent::receive(MsgUaEncodedMessageReceiveInd const& req)
{
    LM(UASRV, LD, "UaEncodedMessageReceiveInd received");

    if (service)
        service->receive(req);
}

} // namespace app::ua::service
