#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "UaServiceSender.hpp"
#include "UaServiceReactor.hpp"

#include "MsgUaServiceInitReq.hpp"
#include "MsgUaServiceConfigReq.hpp"
#include "MsgUaServiceReleaseReq.hpp"
#include "MsgUaEncodedMessageReceiveInd.hpp"

#include <vector>
#include <memory>

namespace app::ua::service
{

class UaService;

class UaServiceComponent : public reactor::ComponentBase<CompIds::compUaService>
{
public:
    explicit UaServiceComponent(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(MsgUaServiceInitReq const&);
    void receive(MsgUaServiceConfigReq const&);
    void receive(MsgUaEncodedMessageReceiveInd const&);
    void receive(MsgUaServiceReleaseReq const&);

private:
    void registerComponent();

    class UaServiceSender : public Sender
    {
    public:
        UaServiceSender(UaServiceComponent& comp_)
            : comp(comp_)
        {}
        void send(MsgUaServiceInitRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaServiceConfigRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaEncodedMessageSendReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaServiceReleaseRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaAssociateSecureChannelReq const& msg) final { comp.getSender().send(msg); }
    private:
        UaServiceComponent& comp;
    };

    UaServiceSender sender;
    Reactor reactor;
    std::unique_ptr<UaService> service;
};

} // namespace app::ua::service
