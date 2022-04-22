#include "ModbusSession.hpp"
#include "LinkInterface.hpp"
#include "ModbusSessionHandler.hpp"
#include "ModbusCodec.hpp"
#include "PduBuffer.hpp"

#include "Logger.hpp"

namespace app::modbus
{

ModbusSession::ModbusSession(ModbusSessionHandler& handler_, int id_)
    : id(id_)
    , handler(handler_)
    , link(nullptr)
{
    reset();
}

ModbusSession::~ModbusSession()
{
}

int ModbusSession::getId() const
{
    return id;
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

void ModbusSession::remove()
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
        LM(MODBUS, LW, "Pdu buffer overflow, reseting");
        reset();
        return;
    }

    int rc = link->receive(pduBuf.end(), pduBuf.capacity());

    if (rc <= 0)
    {
        LM(MODBUS, LD, "Receive return: %d", rc);
        remove();
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
        LM(MODBUS, LW, "Adu is invalid, reseting");
        reset();
        return;
    }

    if (pduBuf.size() != storedAdu.aduLen())
    {
        return;
    }

    switch (storedAdu.func)
    {
    case 0x4:
    {
        storedAdu.startReg = pduBuf.readBe();
        storedAdu.numRegs = pduBuf.readBe();

        LM(MODBUS, LD, "RX ADU: %u:%u LEN=%u START=%u NUM=%u ADDR=%u FC=%u RAW=%s"
            , storedAdu.transactionId, storedAdu.protocolId, storedAdu.pktLen
            , storedAdu.startReg, storedAdu.numRegs, storedAdu.slaveAddr, storedAdu.func, pduBuf.toString().c_str());

        handler.onAduReceived(*this);
    }
    break;
    default:
    {
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
        LM(MODBUS, LD, "Can not send, link is closed");
        return;
    }
    PduBuffer buf;
    ModbusCodec codec(buf);
    codec.encode(adu, data, len);

    LM(MODBUS, LD, "TX ADU: %u:%u LEN=%u START=%u NUM=%u ADDR=%u FC=%u RAW=%s"
        , adu.transactionId, adu.protocolId, buf.size() + 3
        , adu.startReg, adu.numRegs, adu.slaveAddr, adu.func, buf.toString().c_str());

    int rc = link->send(buf.begin(), buf.size());
    if (rc <= 0)
    {
        LM(MODBUS, LD, "Send return: %d", rc);
        remove();
    }
}

void ModbusSession::respondError(ModbusTcpAdu const& adu, ModbusErorr err)
{
    if (!link)
    {
        LM(MODBUS, LD, "Can not send, link is closed");
        return;
    }
    PduBuffer buf;
    ModbusCodec codec(buf);
    codec.encode(adu, err);

    int rc = link->send(buf.begin(), buf.size());
    if (rc <= 0)
    {
        LM(MODBUS, LD, "Send return: %d", rc);
        remove();
    }
}

void ModbusSession::onTimer()
{
}

} // namespace app::modbus
