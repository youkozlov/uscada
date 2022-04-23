#include "ModbusServer.hpp"
#include "AcceptorInterface.hpp"
#include "TimerInterface.hpp"
#include "ModbusSession.hpp"
#include "ModbusAduRsp.hpp"
#include "Logger.hpp"
#include "ReactorInterface.hpp"
#include "ModbusSender.hpp"

namespace app::modbus
{

ModbusServer::ModbusServer(Init const& init)
    : id(init.id)
    , reactor(init.reactor)
    , sessionPool(*this, maxNumSession)
{
}

ModbusServer::~ModbusServer()
{
    LM(MODBUS, LD, "~ModbusServer");
}

void ModbusServer::start()
{
    LM(MODBUS, LD, "Server-%u, start", id);

    acceptor = reactor.createAcceptor(this);

    reactor::LinkAddr addr;
    acceptor->listen(addr);
}

void ModbusServer::stop()
{
    acceptor.reset();
}

void ModbusServer::receive(ModbusAduRsp const& rsp)
{
    LM(CTRL, LD, "ModbusAduRsp: serverId=%d sessionId=%d aduId=%d status=%d numBytes=%u"
        , rsp.serverId, rsp.sessionId, rsp.aduId, rsp.status, rsp.numBytes);

    ModbusSession& session = sessionPool.get(rsp.sessionId);
    ModbusTcpAdu& storedAdu = aduPool.get(rsp.aduId);
    if (MsgStatus::fail == rsp.status)
    {
        session.respondError(storedAdu, ModbusErorr::IllegalDataAddress);
    }
    else
    {
        session.respond(storedAdu, &rsp.data[0], rsp.numBytes);
    }
    aduPool.free(rsp.aduId);
}

void ModbusServer::onAccept()
{
    ModbusSession::Uid uid;
    if (not sessionPool.alloc(uid))
    {
        LM(MODBUS, LE, "Server-%u, can not alloc session from pool", id);
        return;
    }

    ModbusSession& session = sessionPool.get(uid);
    session.setLink(reactor.createLink(&session));
    //session.setTimer(reactor.createTimer(&session));
    acceptor->accept(session.getLink());
}

void ModbusServer::onRemoveSession(ModbusSession& session)
{
    sessionPool.free(session.getId());
}

void ModbusServer::onAduReceived(ModbusSession& session)
{
    int aduId;
    if (not aduPool.alloc(aduId))
    {
        LM(MODBUS, LE, "Server-%u, can not alloc adu from pool", id);
        return;
    }

    ModbusTcpAdu& storedAdu = aduPool.get(aduId);
    storedAdu = session.adu();

    reactor::MsgStore<ModbusAduReq> msgStore;
    ModbusAduReq& req = msgStore.getMsg();

    req.serverId = id;
    req.sessionId = session.getId();
    req.aduId = aduId;
    req.func = storedAdu.isRead() ? ModbusFunc::read : ModbusFunc::write;
    req.startReg = storedAdu.startReg;
    req.numRegs = storedAdu.numRegs;
    req.numBytes = 0;

    Sender::sendMsg(msgStore);
}

} // namespace app::modbus