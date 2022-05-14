#include "ModbusServer.hpp"
#include "AcceptorInterface.hpp"
#include "TimerInterface.hpp"
#include "ModbusSession.hpp"
#include "Logger.hpp"
#include "ModbusReactor.hpp"
#include "MsgModbusAduRsp.hpp"

namespace app::modbus
{

ModbusServer::ModbusServer(Init const& init)
    : id(init.id)
    , addr(init.addr)
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

    acceptor = Reactor::get().createAcceptor([this](){ onAcceptEvent(); });

    acceptor->listen(addr);
}

void ModbusServer::stop()
{
    acceptor.reset();
}

void ModbusServer::receive(MsgModbusAduRsp const& rsp)
{
    LM(MODBUS, LD, "Server-%u, ModbusAduRsp received", id);

    sessionPool.get(rsp.sessionId).receive(rsp);
}

void ModbusServer::onAcceptEvent()
{
    ModbusSession::Uid uid;
    if (not sessionPool.alloc(uid))
    {
        LM(MODBUS, LE, "Server-%u, can not alloc session from pool", id);
        return;
    }

    ModbusSession& session = sessionPool.get(uid);
    session.prepare(id);
    acceptor->accept(session.getLink());
    session.start();
}

void ModbusServer::onReleaseSession(ModbusSession::Uid sessionUid)
{
    LM(MODBUS, LD, "Server-%u, remove session-%u", id, sessionUid);

    sessionPool.free(sessionUid);
}

} // namespace app::modbus