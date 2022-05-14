#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "UaTransportSender.hpp"
#include "UaTransportReactor.hpp"

#include "MsgUaTransportInitReq.hpp"
#include "MsgUaTransportConfigReq.hpp"
#include "MsgUaOpenSecureChannelRsp.hpp"
#include "MsgUaCloseSecureChannelRsp.hpp"
#include "MsgUaSecuredMessageSendReq.hpp"
#include "MsgUaConnectionReleaseReq.hpp"
#include "MsgUaTransportReleaseReq.hpp"

#include <vector>
#include <memory>

namespace app::ua::transport
{

class UaTransport;

class UaTransportComponent : public reactor::ComponentBase<CompIds::compUaTransport>
{
public:
    explicit UaTransportComponent(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(MsgUaTransportInitReq const&);
    void receive(MsgUaTransportConfigReq const&);
    void receive(MsgUaOpenSecureChannelRsp const&);
    void receive(MsgUaCloseSecureChannelRsp const&);
    void receive(MsgUaSecuredMessageSendReq const&);
    void receive(MsgUaConnectionReleaseReq const&);
    void receive(MsgUaTransportReleaseReq const&);

private:
    void registerComponent();

    class UaTransportSender : public Sender
    {
    public:
        UaTransportSender(UaTransportComponent& comp_)
            : comp(comp_)
        {}
        void send(MsgUaTransportInitRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaTransportConfigRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaOpenSecureChannelReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaCloseSecureChannelReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaSecuredMessageReceiveInd const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaConnectionReleaseInd const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaTransportReleaseRsp const& msg) final { comp.getSender().send(msg); }
    private:
        UaTransportComponent& comp;
    };

    UaTransportSender sender;
    Reactor reactor;
    std::unique_ptr<UaTransport> uaTransport;
};

} // namespace app::ua::transport
