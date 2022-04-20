#include "Modbus.hpp"

#include "Logger.hpp"

#include "ModbusInitReq.hpp"
#include "ModbusInitRsp.hpp"
#include "ModbusReleaseReq.hpp"
#include "ModbusReleaseRsp.hpp"
#include "ModbusConfigReq.hpp"
#include "ModbusConfigRsp.hpp"
#include "ModbusDataReq.hpp"
#include "ModbusDataInd.hpp"
#include "ModbusClient.hpp"
#include "ModbusServer.hpp"
#include "ModbusAduRsp.hpp"

namespace app
{

Modbus::Modbus(reactor::SenderInterface& sender, reactor::ReactorInterface& receiver)
    : ComponentBase(sender, receiver)
{
    registerComponent();
}

void Modbus::registerComponent()
{
    getReactor().registerHandler(
          ModbusInitReq::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusInitReq const&>(msg)); }
    );
    getReactor().registerHandler(
          ModbusReleaseReq::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusReleaseReq const&>(msg)); }
    );
    getReactor().registerHandler(
          ModbusConfigReq::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusConfigReq const&>(msg)); }
    );
    getReactor().registerHandler(
          ModbusDataReq::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusDataReq const&>(msg)); }
    );
    getReactor().registerHandler(
          ModbusAduRsp::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusAduRsp const&>(msg)); }
    );
}

void Modbus::receive(ModbusInitReq const&)
{
    LM(MODBUS, LD, "ModbusInitReq received");

    for (size_t i = 0; i < 2; ++i)
    {
        clients.push_back(std::make_unique<ModbusClient>(getSender(), getReactor()));
    }

    server = std::make_unique<ModbusServer>(getSender(), getReactor());

    ModbusInitRsp rsp;
    getSender().send(rsp);
}

void Modbus::receive(ModbusReleaseReq const&)
{
    LM(MODBUS, LD, "ModbusReleaseReq received");

    for (auto& client : clients)
    {
        client.reset();
    }
    server.reset();

    ModbusReleaseRsp rsp;
    getSender().send(rsp);
}

void Modbus::receive(ModbusConfigReq const&)
{
    LM(MODBUS, LD, "ModbusConfigReq received");

    for (auto& client : clients)
    {
        if (client)
            client->start();
    }

    if (server)
        server->start();

    ModbusConfigRsp rsp;
    getSender().send(rsp);
}

void Modbus::receive(ModbusDataReq const&)
{
}

void Modbus::receive(ModbusAduRsp const& rsp)
{
    LM(MODBUS, LD, "ModbusAduRsp received");
    if (server)
        server->receive(rsp);
}

} // namespace app
