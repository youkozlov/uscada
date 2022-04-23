#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "ModbusSender.hpp"
#include <vector>
#include <memory>

namespace app
{
struct ModbusInitReq;
struct ModbusReleaseReq;
struct ModbusConfigReq;
struct ModbusClientAduReq;
struct ModbusAduRsp;
}

namespace app::modbus
{

class ModbusClient;
class ModbusServer;
class Modbus;

class ModbusComponent : public reactor::ComponentBase<CompIds::compModbus>
{
public:
    explicit ModbusComponent(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(ModbusInitReq const&);
    void receive(ModbusConfigReq const&);
    void receive(ModbusClientAduReq const&);
    void receive(ModbusAduRsp const&);
    void receive(ModbusReleaseReq const&);

private:
    void registerComponent();

    class ModbusSender : public Sender
    {
    public:
        ModbusSender(ModbusComponent& comp_)
            : comp(comp_)
        {}
        void send(ModbusInitRsp const& msg) final { comp.getSender().send(msg); }
        void send(ModbusConfigRsp const& msg) final { comp.getSender().send(msg); }
        void send(ModbusAduReq const& msg) final { comp.getSender().send(msg); }
        void send(ModbusClientAduRsp const& msg) final { comp.getSender().send(msg); }
        void send(ModbusReleaseRsp const& msg) final { comp.getSender().send(msg); }
    private:
        ModbusComponent& comp;
    };

    ModbusSender modbusSender;

    std::unique_ptr<Modbus> modbus;
};

} // namespace app::modbus
