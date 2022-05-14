#pragma once

#include <array>
#include <memory>

#include "MsgControllerStartReq.hpp"
#include "MsgControllerStopReq.hpp"
#include "MsgModbusInitReq.hpp"
#include "MsgModbusInitRsp.hpp"
#include "MsgModbusReleaseReq.hpp"
#include "MsgModbusReleaseRsp.hpp"
#include "MsgModbusConfigReq.hpp"
#include "MsgModbusConfigRsp.hpp"
#include "MsgModbusClientAduReq.hpp"
#include "MsgModbusClientAduRsp.hpp"
#include "MsgModbusAduReq.hpp"
#include "MsgModbusAduRsp.hpp"
#include "MsgUaSecureChannelInitRsp.hpp"
#include "MsgUaSecureChannelConfigRsp.hpp"
#include "MsgUaSecureChannelReleaseRsp.hpp"
#include "MsgUaTransportInitRsp.hpp"
#include "MsgUaTransportConfigRsp.hpp"
#include "MsgUaTransportReleaseRsp.hpp"
#include "MsgUaServiceInitRsp.hpp"
#include "MsgUaServiceConfigRsp.hpp"
#include "MsgUaServiceReleaseRsp.hpp"

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "ControllerSender.hpp"
#include "ControllerReactor.hpp"
#include "ModbusTestController.hpp"
#include "UaController.hpp"

namespace app::controller
{

class ControllerComponent : public reactor::ComponentBase<CompIds::compController>
{
public:
    explicit ControllerComponent(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(MsgControllerStartReq const&);
    void receive(MsgControllerStopReq const&);
    void receive(MsgModbusInitRsp const&);
    void receive(MsgModbusReleaseRsp const&);
    void receive(MsgModbusConfigRsp const&);
    void receive(MsgModbusClientAduRsp const&);
    void receive(MsgModbusAduReq const&);
    void receive(MsgUaSecureChannelInitRsp const&);
    void receive(MsgUaSecureChannelConfigRsp const&);
    void receive(MsgUaSecureChannelReleaseRsp const&);
    void receive(MsgUaTransportInitRsp const&);
    void receive(MsgUaTransportConfigRsp const&);
    void receive(MsgUaTransportReleaseRsp const&);
    void receive(MsgUaServiceInitRsp const&);
    void receive(MsgUaServiceConfigRsp const&);
    void receive(MsgUaServiceReleaseRsp const&);
private:
    void registerComponent();

    class ControllerSender : public Sender
    {
    public:
        ControllerSender(ControllerComponent& comp_)
            : comp(comp_)
        {}
        void send(MsgModbusInitReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgModbusReleaseReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgModbusConfigReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgModbusClientAduReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgModbusAduRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaSecureChannelInitReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaSecureChannelConfigReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaSecureChannelReleaseReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaTransportInitReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaTransportConfigReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaTransportReleaseReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaServiceInitReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaServiceConfigReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgUaServiceReleaseReq const& msg) final { comp.getSender().send(msg); }
    private:
        ControllerComponent& comp;
    };

    ControllerSender sender;
    Reactor reactor;
    std::unique_ptr<ModbusTestController> modbus;
    std::unique_ptr<UaController> opcUa;
};

} // namespace app::controller
