#include "Modbus.hpp"
#include "ModbusSender.hpp"

#include "Logger.hpp"

namespace app::modbus
{

Modbus::Modbus(Init const& init)
    : reactor(init.reactor)
    , servers(init.maxNumServers)
    , clients(init.maxNumClients)
{
    LM(MODBUS, LD, "Init maxNumServers: %u, maxNumClients: %u", init.maxNumServers, init.maxNumClients);
}

Modbus::~Modbus()
{
}

void Modbus::receive(ModbusConfigReq const& req)
{
    for (unsigned i = 0; i < req.numItems; ++i)
    {
        ModbusConfig const& item = req.items[i];
        switch (item.mode)
        {
        case ModbusConfig::Mode::server:
        {
            if (item.id >= servers.size())
            {
                LM(MODBUS, LE, "Invalid serverId", item.id);
                continue;
            }
            ModbusServer::Init init{reactor, item.id};
            servers[item.id] = std::make_unique<ModbusServer>(init);
            servers[item.id]->start();
        }
        break;
        case ModbusConfig::Mode::client:
        {
            if (item.id >= clients.size())
            {
                LM(MODBUS, LE, "Invalid clientId", item.id);
                continue;
            }
            ModbusClient::Init init{reactor, item.id};
            clients[item.id] = std::make_unique<ModbusClient>(init);
            clients[item.id]->start();
        }
        break;
        }
    }

    reactor::MsgStore<ModbusConfigRsp> msgStore;
    ModbusConfigRsp& rsp = msgStore.getMsg();
    rsp.numItems = req.numItems;
    for (unsigned i = 0; i < req.numItems; ++i)
    {
        rsp.items[i].id = req.items[i].id;
        rsp.items[i].status = MsgStatus::success;
    }
    Sender::sendMsg(msgStore);
}

void Modbus::receive(ModbusClientAduReq const& msg)
{
    if (msg.clientId >= clients.size() || !clients[msg.clientId])
    {
        LM(MODBUS, LE, "Invalid clientId, %u", msg.clientId);
        return;
    }
    clients[msg.clientId]->receive(msg);
}

void Modbus::receive(ModbusAduRsp const& msg)
{
    if (msg.serverId >= servers.size())
    {
        LM(MODBUS, LE, "Invalid serverId, %u", msg.serverId);
        return;
    }
    if (not servers[msg.serverId])
    {
        LM(MODBUS, LE, "Server-%u is undefined", msg.serverId);
        return;
    }
    servers[msg.serverId]->receive(msg);
}

} // namespace app
