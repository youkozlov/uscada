#pragma once

#include <array>
#include <memory>

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "ControllerSender.hpp"
#include "ControllerReactor.hpp"
#include "ModbusTestController.hpp"
#include "OpcUaController.hpp"

namespace app
{
struct ControllerStartReq;
struct ControllerStopReq;
struct ModbusInitRsp;
struct ModbusReleaseRsp;
struct ModbusConfigRsp;
struct ModbusClientAduRsp;
struct ModbusAduReq;
}

namespace app::controller
{

class ControllerComponent : public reactor::ComponentBase<CompIds::compController>
{
public:
    explicit ControllerComponent(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(ControllerStartReq const&);
    void receive(ControllerStopReq const&);
    void receive(ModbusInitRsp const&);
    void receive(ModbusReleaseRsp const&);
    void receive(ModbusConfigRsp const&);
    void receive(ModbusClientAduRsp const&);
    void receive(ModbusAduReq const&);

private:
    void registerComponent();

    class ControllerSender : public Sender
    {
    public:
        ControllerSender(ControllerComponent& comp_)
            : comp(comp_)
        {}
        void send(ModbusInitReq const& msg) final { comp.getSender().send(msg); }
        void send(ModbusReleaseReq const& msg) final { comp.getSender().send(msg); }
        void send(ModbusConfigReq const& msg) final { comp.getSender().send(msg); }
        void send(ModbusClientAduReq const& msg) final { comp.getSender().send(msg); }
        void send(ModbusAduRsp const& msg) final { comp.getSender().send(msg); }
    private:
        ControllerComponent& comp;
    };

    ControllerSender sender;
    Reactor reactor;
    std::unique_ptr<ModbusTestController> modbus;
    std::unique_ptr<OpcUaController> opcUa;
};

} // namespace app::controller
