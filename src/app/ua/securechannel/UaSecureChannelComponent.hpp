#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "UaSecureChannelSender.hpp"
#include "UaSecureChannelReactor.hpp"

#include "MsgUaSecureChannelInitReq.hpp"
#include "MsgUaSecureChannelConfigReq.hpp"
#include "MsgUaOpenSecureChannelReq.hpp"
#include "MsgUaCloseSecureChannelReq.hpp"
#include "MsgUaAssociateSecureChannelReq.hpp"
#include "MsgUaSecuredMessageReceiveInd.hpp"
#include "MsgUaConnectionReleaseInd.hpp"
#include "MsgUaEncodedMessageSendReq.hpp"
#include "MsgUaSecureChannelReleaseReq.hpp"

#include <vector>
#include <memory>

namespace app::ua::securechannel
{

class UaSecureChannel;

class UaSecureChannelComponent : public reactor::ComponentBase<CompIds::compUaSecChannel>
{
public:
    explicit UaSecureChannelComponent(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(MsgUaSecureChannelInitReq const&);
    void receive(MsgUaSecureChannelConfigReq const&);
    void receive(MsgUaSecuredMessageReceiveInd const&);
    void receive(MsgUaOpenSecureChannelReq const&);
    void receive(MsgUaCloseSecureChannelReq const&);
    void receive(MsgUaAssociateSecureChannelReq const&);
    void receive(MsgUaConnectionReleaseInd const&);
    void receive(MsgUaEncodedMessageSendReq const&);
    void receive(MsgUaSecureChannelReleaseReq const&);

private:
    void registerComponent();

    class UaSecureChannelSender : public Sender
    {
    public:
        UaSecureChannelSender(UaSecureChannelComponent& comp_)
            : comp(comp_)
        {}
        void send(MsgUaSecureChannelInitRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaSecureChannelConfigRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaOpenSecureChannelRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaCloseSecureChannelRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaSecuredMessageSendReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaConnectionReleaseReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaEncodedMessageReceiveInd const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaSecureChannelReleaseRsp const& msg) final { comp.getSender().send(msg); }
    private:
        UaSecureChannelComponent& comp;
    };

    UaSecureChannelSender sender;
    Reactor reactor;
    std::unique_ptr<UaSecureChannel> secureChannel;
};

} // namespace app::ua::securechannel
