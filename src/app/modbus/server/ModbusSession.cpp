#include "ModbusSession.hpp"
#include "LinkInterface.hpp"
#include "ModbusSessionHandler.hpp"
#include "ModbusCodec.hpp"
#include "PduBuffer.hpp"

#include "Logger.hpp"

namespace app::modbus
{

ModbusSession::ModbusSession(ModbusSessionHandler& handler_, Uid uid_)
    : uid(uid_)
    , handler(handler_)
{
    reset();
}

ModbusSession::~ModbusSession()
{
}

ModbusSession::Uid ModbusSession::getId() const
{
    return uid;
}

void ModbusSession::setLink(reactor::LinkPtr link_)
{
    link = std::move(link_);
}

void ModbusSession::setTimer(reactor::TimerPtr timer_)
{
    timer = std::move(timer_);
}

reactor::LinkInterface& ModbusSession::getLink() const
{
    return *link;
}

ModbusTcpAdu const& ModbusSession::adu() const
{
    return storedAdu;
}

PduBuffer const& ModbusSession::pdu() const
{
    return pduBuf;
}

void ModbusSession::reset()
{
    pduBuf.reset();
    storedAdu.reset();
}

void ModbusSession::release()
{
    reset();
    link.reset();
    timer.reset();
    handler.onRemoveSession(*this);
}

void ModbusSession::onDataReceived()
{
    if (0 == pduBuf.capacity())
    {
        LM(MODBUS, LW, "Session-%u, pdu buffer overflow, reseting", uid);
        reset();
        return;
    }

    int rc = link->receive(pduBuf.end(), pduBuf.capacity());

    if (rc <= 0)
    {
        LM(MODBUS, LD, "Session-%u, receive return: %d", uid, rc);
        release();
        return;
    }

    pduBuf.seek(rc);

    if (pduBuf.size() < storedAdu.aduHdrLen())
    {
        return;
    }

    if (not storedAdu.isDecoded())
    {
        ModbusCodec codec(pduBuf);
        codec.decode(storedAdu);
    }

    if (not storedAdu.isValid())
    {
        LM(MODBUS, LW, "Session-%u, adu is invalid", uid);
        respondError(storedAdu, ModbusErorr::IllegalFunction);
        reset();
        return;
    }

    if (pduBuf.size() != storedAdu.aduLen())
    {
        return;
    }

    if (pduBuf.size() > storedAdu.aduLen())
    {
        LM(MODBUS, LW, "Session-%u, adu is invalid", uid);
        respondError(storedAdu, ModbusErorr::IllegalFunction);
        reset();
        return;
    }

    switch (storedAdu.func)
    {
    case 0x4:
    {
        storedAdu.startReg = pduBuf.readBe();
        storedAdu.numRegs = pduBuf.readBe();

        LM(MODBUS, LD, "Session-%u, RX ADU: %u:%u LEN=%u START=%u NUM=%u ADDR=%u FC=%u RAW=%s"
            , uid, storedAdu.transactionId, storedAdu.protocolId, storedAdu.pktLen
            , storedAdu.startReg, storedAdu.numRegs, storedAdu.slaveAddr, storedAdu.func, pduBuf.toString().c_str());

        handler.onAduReceived(*this);
    }
    break;
    default:
    {
        LM(MODBUS, LW, "Session-%u, function is unsupported", uid);
        respondError(storedAdu, ModbusErorr::IllegalFunction);
    }
    break;
    }

    reset();
}

void ModbusSession::respond(ModbusTcpAdu const& adu, void const* data, unsigned len)
{
    if (!link)
    {
        LM(MODBUS, LD, "Session-%u, can not send, link is undefined", uid);
        return;
    }
    PduBuffer buf;
    ModbusCodec codec(buf);
    codec.encode(adu, data, len);

    LM(MODBUS, LD, "Session-%u, TX ADU: %u:%u LEN=%u START=%u NUM=%u ADDR=%u FC=%u RAW=%s"
        , uid, adu.transactionId, adu.protocolId, buf.size() + 3
        , adu.startReg, adu.numRegs, adu.slaveAddr, adu.func, buf.toString().c_str());

    int rc = link->send(buf.begin(), buf.size());
    if (rc <= 0)
    {
        LM(MODBUS, LD, "Session-%u, send return: %d", uid, rc);
        release();
    }
}

void ModbusSession::respondError(ModbusTcpAdu const& adu, ModbusErorr err)
{
    if (!link)
    {
        LM(MODBUS, LD, "Session-%u, can not send, link is undefined", uid);
        return;
    }
    PduBuffer buf;
    ModbusCodec codec(buf);
    codec.encode(adu, err);

    LM(MODBUS, LD, "Session-%u, TX ERR ADU: %u:%u LEN=%u ADDR=%u ERR=%u RAW=%s"
        , uid, adu.transactionId, adu.protocolId, 3
        , adu.slaveAddr, err, buf.toString().c_str());

    int rc = link->send(buf.begin(), buf.size());
    if (rc <= 0)
    {
        LM(MODBUS, LD, "Session-%u, send return: %d", uid, rc);
        release();
    }
}

void ModbusSession::onTimer()
{
    LM(MODBUS, LD, "Session-%u, timeout", uid);
    release();
}

} // namespace app::modbus
