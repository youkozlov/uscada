#include "ModbusComponent.hpp"

#include "MsgModbusInitReq.hpp"
#include "MsgModbusReleaseReq.hpp"
#include "MsgModbusConfigReq.hpp"
#include "MsgModbusClientAduReq.hpp"
#include "MsgModbusAduRsp.hpp"

#include "ModbusClient.hpp"
#include "ModbusServer.hpp"
#include "Modbus.hpp"

#include "Logger.hpp"

namespace app::modbus
{

ModbusComponent::ModbusComponent(reactor::SenderInterface& sender, reactor::ReactorInterface& reactor)
    : ComponentBase(sender, reactor)
    , modbusSender(*this)
    , modbusReactor(reactor)
{
    registerComponent();
}

void ModbusComponent::registerComponent()
{
    getReactor().registerHandlers
    ({
          { MsgModbusInitReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgModbusInitReq const&>(msg)); }}
        , { MsgModbusReleaseReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgModbusReleaseReq const&>(msg)); }}
        , { MsgModbusConfigReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgModbusConfigReq const&>(msg)); } }
        , { MsgModbusClientAduReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgModbusClientAduReq const&>(msg)); }}
        , { MsgModbusAduRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgModbusAduRsp const&>(msg)); }}
    });
}

void ModbusComponent::receive(MsgModbusInitReq const& req)
{
    LM(MODBUS, LD, "ModbusInitReq received");

    Modbus::Init init{req.maxNumServers, req.maxNumClients};
    modbus = std::make_unique<Modbus>(init);

    reactor::MsgStore<MsgModbusInitRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void ModbusComponent::receive(MsgModbusReleaseReq const&)
{
    LM(MODBUS, LD, "ModbusReleaseReq received");

    modbus.reset();

    reactor::MsgStore<MsgModbusReleaseRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void ModbusComponent::receive(MsgModbusConfigReq const& req)
{
    LM(MODBUS, LD, "ModbusConfigReq received");

    if (modbus)
        modbus->receive(req);
}

void ModbusComponent::receive(MsgModbusClientAduReq const& req)
{
    LM(MODBUS, LD, "ModbusClientAduReq received");

    if (modbus)
        modbus->receive(req);
}

void ModbusComponent::receive(MsgModbusAduRsp const& rsp)
{
    LM(MODBUS, LD, "ModbusAduRsp received");
    if (modbus)
        modbus->receive(rsp);
}

} // namespace app::modbus
