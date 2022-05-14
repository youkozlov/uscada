#include "ModbusSession.hpp"
#include "LinkInterface.hpp"
#include "ModbusSessionHandler.hpp"
#include "ModbusCodec.hpp"
#include "AduRespond.hpp"
#include "ModbusSender.hpp"
#include "ModbusReactor.hpp"

#include "Logger.hpp"

namespace app::modbus
{

ModbusSession::ModbusSession(ModbusSessionHandler& handler_, Uid uid_)
    : uid(uid_)
    , fsm(*this)
    , handler(handler_)
    , storedAdu(&storedAduBuf[0])
{
}

ModbusSession::~ModbusSession()
{
}

void ModbusSession::prepare(EntityId val)
{
    serverId = val;
    timer = Reactor::get().createTimer([this](){ onTimerEvent(); });
    link = Reactor::get().createLink([this](auto ev){ onLinkEvent(ev); });
}

reactor::LinkInterface& ModbusSession::getLink()
{
    return *link;
}

void ModbusSession::start()
{
    fsm.getState().onStart(fsm);
}

void ModbusSession::receive(MsgModbusAduRsp const& rsp)
{
    fsm.getState().onModbusAduRspReceive(fsm, rsp);
}

void ModbusSession::onLinkEvent(reactor::LinkEvent ev)
{
    switch (ev)
    {
    case reactor::LinkEvent::data:
        fsm.getState().onDataReceived(fsm);
    break;
    case reactor::LinkEvent::connected:
    case reactor::LinkEvent::error:
        LM(MODBUS, LE, "Session-%u, unexpected", uid);
    break;
    }
}

void ModbusSession::onTimerEvent()
{
    fsm.getState().onTimer(fsm);
}



void ModbusSession::startTimer(long timeout)
{
    timer->start(timeout);
}

void ModbusSession::stopTimer()
{
    timer->stop();
}

void ModbusSession::receivePreaction()
{
    pduBuf.reset();
}

Result ModbusSession::receive()
{
    if (pduBuf.size() > maxAduLen)
    {
        LM(MODBUS, LW, "Client-%u, received ADU is invalid", uid);
        return Result::done;
    }

    auto const& result = link->receive(pduBuf.end(), pduBuf.capacity());
    switch (result.status)
    {
    case reactor::LinkResult::ok:
    break;
    case reactor::LinkResult::na:
        return Result::noerror;
    case reactor::LinkResult::closed:
    case reactor::LinkResult::error:
        return Result::error;
    }

    pduBuf.seek(result.len);

    ModbusCodec codec(pduBuf);

    if (not codec.isAduHdrReceived())
    {
        return Result::noerror;
    }

    if (not codec.isAduDataLenValid())
    {
        return Result::error;
    }

    if (not codec.isAduReceived())
    {
        return Result::noerror;
    }

    if (not codec.isAduValid())
    {
        LM(MODBUS, LW, "Session-%u, PDU is invalid", uid);
        // TODO provide error to client
        return Result::done;
    }

    LM(MODBUS, LD, "Session-%u, RX PDU %s", uid, pduBuf.toString().c_str());

    if (not codec.decode(storedAdu))
    {
        LM(MODBUS, LW, "Session-%u, ADU decode error", uid);
        // TODO provide error to client
        return Result::done;
    }

    reactor::MsgStore<MsgModbusAduReq> msgStore;
    MsgModbusAduReq& req = msgStore.getMsg();

    req.serverId = serverId;
    req.sessionId = uid;
    req.transactId = storedAdu.transactId;
    req.func = storedAdu.func;
    req.addr = storedAdu.addr;
    req.startItem = storedAdu.startItem;
    req.numItems = storedAdu.numItems;
    req.numBytes = storedAdu.numBytes;
    std::memcpy(req.data, storedAdu.data, storedAdu.numBytes);
    Sender::sendMsg(msgStore);

    return Result::done;
}

Result ModbusSession::send(MsgModbusAduRsp const& rsp)
{
    if (rsp.transactId != storedAdu.transactId)
    {
        LM(MODBUS, LE, "Session-%u, transactId is unexpected %u vs %u"
            , uid, storedAdu.transactId, rsp.transactId);
        return Result::done;
    }

    if (rsp.status != MsgStatus::success)
    {
        LM(MODBUS, LE, "Session-%u, modbusAduRsp error status", uid);
        return Result::done;
    }

    AduRespond aduRsp;
    aduRsp.transactId = rsp.transactId;
    aduRsp.func = (rsp.error != ModbusError::noerror) ? ModbusFunction::modbusError : storedAdu.func;
    aduRsp.addr = storedAdu.addr;
    aduRsp.error = rsp.error;
    aduRsp.startItem = storedAdu.startItem;
    aduRsp.numItems = storedAdu.numItems;
    aduRsp.numBytes = rsp.numBytes;
    std::memcpy(aduRsp.data, rsp.data, rsp.numBytes);

    PduBuffer buf;
    ModbusCodec codec(buf);

    if (not codec.encode(aduRsp))
    {
        LM(MODBUS, LE, "Session-%u, ADU decode error", uid);
        // TODO provide error to client
        return Result::done;
    }

    if (not codec.isAduValid())
    {
        LM(MODBUS, LE, "Session-%u, PDU is invalid", uid);
        // TODO provide error to client
        return Result::done;
    }

    LM(MODBUS, LD, "Session-%u, TX PDU %s", uid, buf.toString().c_str());

    int rc = link->send(buf.begin(), buf.size());
    if (rc <= 0)
    {
        LM(MODBUS, LI, "Client-%u, send return: %d", uid, rc);
        return Result::error;
    }

    return Result::done;
}

void ModbusSession::releaseSession()
{
    link.reset();
    timer.reset();
    handler.onReleaseSession(uid);
}

} // namespace app::modbus
