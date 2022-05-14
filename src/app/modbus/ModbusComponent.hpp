#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "ModbusSender.hpp"
#include "ModbusReactor.hpp"
#include <vector>
#include <memory>

namespace app
{
struct MsgModbusInitReq;
struct MsgModbusReleaseReq;
struct MsgModbusConfigReq;
struct MsgModbusClientAduReq;
struct MsgModbusAduRsp;
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

    void receive(MsgModbusInitReq const&);
    void receive(MsgModbusConfigReq const&);
    void receive(MsgModbusClientAduReq const&);
    void receive(MsgModbusAduRsp const&);
    void receive(MsgModbusReleaseReq const&);

private:
    void registerComponent();

    class ModbusSender : public Sender
    {
    public:
        ModbusSender(ModbusComponent& comp_)
            : comp(comp_)
        {}
        void send(MsgModbusInitRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgModbusConfigRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgModbusAduReq const& msg) final { comp.getSender().send(msg); }
        void send(MsgModbusClientAduRsp const& msg) final { comp.getSender().send(msg); }
        void send(MsgModbusReleaseRsp const& msg) final { comp.getSender().send(msg); }
    private:
        ModbusComponent& comp;
    };

    ModbusSender modbusSender;
    Reactor modbusReactor;
    std::unique_ptr<Modbus> modbus;
};

} // namespace app::modbus
