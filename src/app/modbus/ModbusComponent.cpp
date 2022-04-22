#include "ModbusComponent.hpp"

#include "Logger.hpp"

#include "ModbusInitReq.hpp"
#include "ModbusReleaseReq.hpp"
#include "ModbusConfigReq.hpp"
#include "ModbusClient.hpp"
#include "ModbusServer.hpp"
#include "ModbusClientAduReq.hpp"
#include "ModbusAduRsp.hpp"
#include "Modbus.hpp"

namespace app::modbus
{

ModbusComponent::ModbusComponent(reactor::SenderInterface& sender, reactor::ReactorInterface& receiver)
    : ComponentBase(sender, receiver)
    , modbusSender(*this)
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

void ModbusComponent::receive(ModbusInitReq const&)
{
    LM(MODBUS, LD, "ModbusInitReq received");

    modbus = std::make_unique<Modbus>();

    for (size_t i = 0; i < 2; ++i)
    {
        clients.push_back(std::make_unique<ModbusClient>(getReactor()));
    }

    server = std::make_unique<ModbusServer>(getReactor());

    reactor::MsgStore<ModbusInitRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void ModbusComponent::receive(ModbusReleaseReq const&)
{
    LM(MODBUS, LD, "ModbusReleaseReq received");

    modbus.reset();

    for (auto& client : clients)
    {
        client.reset();
    }
    server->stop();
    server.reset();

    reactor::MsgStore<ModbusReleaseRsp> msgStore;
    Sender::sendMsg(msgStore);
}

void ModbusComponent::receive(ModbusConfigReq const& req)
{
    LM(MODBUS, LD, "ModbusConfigReq received");

    for (auto& client : clients)
    {
        if (client)
            client->start();
    }

    if (server)
        server->start();

    reactor::MsgStore<ModbusConfigRsp> msgStore;
    ModbusConfigRsp& rsp = msgStore.getMsg();
    rsp.numItems = req.numItems;
    for (unsigned i = 0; i < req.numItems; i++)
    {
        rsp.items[i].id = req.items[i].id;
        rsp.items[i].status = MsgStatus::success;
    }
    Sender::sendMsg(msgStore);
}

void ModbusComponent::receive(ModbusClientAduReq const& req)
{
    LM(MODBUS, LD, "ModbusClientAduReq received");

    for (auto& client : clients)
    {
        if (client)
            client->receive(req);
    }
}

void ModbusComponent::receive(ModbusAduRsp const& rsp)
{
    LM(MODBUS, LD, "ModbusAduRsp received");
    if (server)
        server->receive(rsp);
}

} // namespace app::modbus
