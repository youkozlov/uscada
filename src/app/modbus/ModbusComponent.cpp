#include "ModbusComponent.hpp"

#include "ModbusInitReq.hpp"
#include "ModbusReleaseReq.hpp"
#include "ModbusConfigReq.hpp"
#include "ModbusClient.hpp"
#include "ModbusServer.hpp"
#include "ModbusClientAduReq.hpp"
#include "ModbusAduRsp.hpp"
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
          { ModbusInitReq::msgId(), [this](auto const& msg){ receive(static_cast<ModbusInitReq const&>(msg)); }}
        , { ModbusReleaseReq::msgId(), [this](auto const& msg){ receive(static_cast<ModbusReleaseReq const&>(msg)); }}
        , { ModbusConfigReq::msgId(), [this](auto const& msg){ receive(static_cast<ModbusConfigReq const&>(msg)); } }
        , { ModbusClientAduReq::msgId(), [this](auto const& msg){ receive(static_cast<ModbusClientAduReq const&>(msg)); }}
        , { ModbusAduRsp::msgId(), [this](auto const& msg){ receive(static_cast<ModbusAduRsp const&>(msg)); }}
    });
}

void ModbusComponent::receive(ModbusInitReq const& req)
{
    LM(MODBUS, LD, "ModbusInitReq received");

    Modbus::Init init{getReactor(), req.maxNumServers, req.maxNumClients};
    modbus = std::make_unique<Modbus>(init);

    reactor::MsgStore<ModbusInitRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void ModbusComponent::receive(ModbusReleaseReq const&)
{
    LM(MODBUS, LD, "ModbusReleaseReq received");

    modbus.reset();

    reactor::MsgStore<ModbusReleaseRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void ModbusComponent::receive(ModbusConfigReq const& req)
{
    LM(MODBUS, LD, "ModbusConfigReq received");

    if (modbus)
        modbus->receive(req);
}

void ModbusComponent::receive(ModbusClientAduReq const& req)
{
    LM(MODBUS, LD, "ModbusClientAduReq received");

    if (modbus)
        modbus->receive(req);
}

void ModbusComponent::receive(ModbusAduRsp const& rsp)
{
    LM(MODBUS, LD, "ModbusAduRsp received");
    if (modbus)
        modbus->receive(rsp);
}

} // namespace app::modbus
