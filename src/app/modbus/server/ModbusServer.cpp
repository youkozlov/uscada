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

ModbusServer::ModbusServer(reactor::ReactorInterface& reactor_)
    : reactor(reactor_)
    , acceptor(reactor_.createAcceptor(*this))
    , sessionPool(*this)
{
}

ModbusServer::~ModbusServer()
{
    LM(MODBUS, LD, "~ModbusServer");
}

void ModbusServer::start()
{
    reactor::LinkAddr addr;
    acceptor->listen(addr);
}

void ModbusServer::stop()
{
    //reactor.releaseAcceptor(acceptor);
    acceptor->close();
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
    session.setLink(reactor.createLink(&session));
    //session.setTimer(reactor.createTimer(session));
    acceptor->accept(session.getLink());
}

void ModbusServer::onAccept()
{
    createSession();
}

void ModbusServer::onRemoveSession(ModbusSession& session)
{
    LM(MODBUS, LD, "Remove session");

    sessionPool.free(session.getId());
}

void ModbusServer::onAduReceived(ModbusSession& session)
{
    int aduId;
    if (not aduPool.alloc(aduId))
    {
        LM(MODBUS, LE, "Can not alloc adu from pool");
        return;
    }

    ModbusTcpAdu& storedAdu = aduPool.get(aduId);
    storedAdu = session.adu();

    reactor::MsgStore<ModbusAduReq> msgStore;
    ModbusAduReq& req = msgStore.getMsg();

    req.serverId = 0;
    req.sessionId = session.getId();
    req.aduId = aduId;
    req.func = storedAdu.isRead() ? ModbusFunc::read : ModbusFunc::write;
    req.startReg = storedAdu.startReg;
    req.numRegs = storedAdu.numRegs;
    req.numBytes = 0;

    Sender::sendMsg(msgStore);
}

} // namespace app::modbus