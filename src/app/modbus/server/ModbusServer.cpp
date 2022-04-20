#include "ModbusServer.hpp"
#include "AcceptorInterface.hpp"
#include "ModbusSession.hpp"
#include "ModbusAduReq.hpp"
#include "ModbusAduRsp.hpp"
#include "Logger.hpp"

namespace app
{

ModbusServer::ModbusServer(reactor::SenderInterface& sender_, reactor::ReactorInterface& reactor_)
    : sender(sender_)
    , reactor(reactor_)
    , acceptor(reactor.createAcceptor(*this))
    , sessionPool(*this)
{
}

ModbusServer::~ModbusServer()
{
}

void ModbusServer::start()
{
    reactor::LinkAddr addr;
    acceptor->listen(addr);
}

void ModbusServer::receive(ModbusAduRsp const& rsp)
{
    ModbusSession& session = sessionPool.get(rsp.sessionId);
    ModbusTcpAdu& storedAdu = aduPool.get(rsp.aduId);

    if (session.isActive())
    {
        session.respond(storedAdu);
    }

    aduPool.free(rsp.aduId);
}

void ModbusServer::onAccept()
{
    createSession();
}

void ModbusServer::createSession()
{
    LM(MODBUS, LD, "Create session");

    int id;
    if (not sessionPool.alloc(id))
    {
        LM(MODBUS, LE, "Can not alloc session from pool");
        return;
    }

    ModbusSession& session = sessionPool.get(id);
    session.setLink(reactor.createLink(session));
    acceptor->accept(session.getLink());
}

void ModbusServer::removeSession(ModbusSession& session)
{
    LM(MODBUS, LD, "Remove session");

    sessionPool.free(session.getId());
    session.setLink(nullptr);
}

void ModbusServer::onAduReceived(ModbusSession& session)
{
    LM(MODBUS, LD, "Adu received");

    int aduId;
    if (not aduPool.alloc(aduId))
    {
        LM(MODBUS, LE, "Can not alloc adu from pool");
        return;
    }

    ModbusTcpAdu& storedAdu = aduPool.get(aduId);
    storedAdu = session.adu();

    ModbusAduReq req;
    req.serverId = 0;
    req.sessionId = session.getId();
    req.aduId = aduId;
    req.func = ModbusFunc::read;
    req.start = storedAdu.startReg;
    req.numItems = storedAdu.numRegs;

    sender.send(req);
}

} // namespace app