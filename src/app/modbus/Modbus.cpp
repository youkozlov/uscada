#include "Modbus.hpp"
#include "ModbusSender.hpp"

#include "Logger.hpp"

namespace app::modbus
{

Modbus::Modbus(Init const& init)
    : servers(init.maxNumServers)
    , clients(init.maxNumClients)
{
    LM(MODBUS, LD, "Init maxNumServers: %zu, maxNumClients: %zu", init.maxNumServers, init.maxNumClients);
}

Modbus::~Modbus()
{
}

void Modbus::receive(MsgModbusConfigReq const& req)
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
                LM(MODBUS, LE, "Invalid serverId, %u", item.id);
                continue;
            }
            ModbusServer::Init init{item.id, item.addr};
            servers[item.id] = std::make_unique<ModbusServer>(init);
            servers[item.id]->start();
        }
        break;
        case ModbusConfig::Mode::client:
        {
            if (item.id >= clients.size())
            {
                LM(MODBUS, LE, "Invalid clientId, %u", item.id);
                continue;
            }
            ModbusClient::Init init{item.id, item.addr};
            clients[item.id] = std::make_unique<ModbusClient>(init);
            clients[item.id]->start();
        }
        break;
        }
    }

    reactor::MsgStore<MsgModbusConfigRsp> msgStore;
    MsgModbusConfigRsp& rsp = msgStore.getMsg();
    rsp.numItems = req.numItems;
    for (unsigned i = 0; i < req.numItems; ++i)
    {
        rsp.items[i].id = req.items[i].id;
        rsp.items[i].status = MsgStatus::success;
    }
    Sender::sendMsg(msgStore);
}

void Modbus::receive(MsgModbusClientAduReq const& req)
{
    for (unsigned i = 0; i < req.numItems; ++i)
    {
        auto const& item = req.item(i);

        if (item.clientId >= clients.size() || not clients[item.clientId])
        {
            LM(MODBUS, LE, "Invalid clientId, %u", item.clientId);
            reactor::MsgStore<MsgModbusClientAduRsp> msgStore;
            MsgModbusClientAduRsp& rsp = msgStore.getMsg();
            rsp.clientId = item.clientId;
            rsp.transactId = item.transactId;
            rsp.error = ModbusError::noerror;
            rsp.status = MsgStatus::error;
            rsp.numBytes = 0;
            Sender::sendMsg(msgStore);
            continue;
        }
        clients[item.clientId]->receive(item);
    }
}

void Modbus::receive(MsgModbusAduRsp const& msg)
{
    if (msg.serverId >= servers.size() || not servers[msg.serverId])
    {
        LM(MODBUS, LE, "Invalid serverId, %u", msg.serverId);
        return;
    }
    servers[msg.serverId]->receive(msg);
}

} // namespace app
