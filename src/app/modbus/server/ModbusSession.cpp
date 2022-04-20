#include "ModbusSession.hpp"
#include "LinkInterface.hpp"
#include "ModbusServer.hpp"
#include "Logger.hpp"
#include "ModbusCodec.hpp"
#include "PduBuffer.hpp"

namespace app
{

ModbusSession::ModbusSession(ModbusServer& server_, int id_)
    : id(id_)
    , server(server_)
{
    reset();
}

ModbusSession::~ModbusSession()
{
    if (link)
        link->close();
}

int ModbusSession::getId() const
{
    return id;
}

void ModbusSession::setLink(reactor::LinkPtr link_)
{
    link = std::move(link_);
}

reactor::LinkInterface& ModbusSession::getLink() const
{
    return *link;
}

bool ModbusSession::isActive() const
{
    return nullptr != link;
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

void ModbusSession::onDataReceived()
{
    if (0 == pduBuf.capacity())
    {
        LM(MODBUS, LE, "Pdu buffer overflow, reseting");
        reset();
        return;
    }

    int rc = link->receive(pduBuf.end(), pduBuf.capacity());

    if (rc <= 0)
    {
        reset();
        link->close();
        server.removeSession(*this);
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
        LM(MODBUS, LE, "Adu is invalid, reseting");
        reset();
        return;
    }

    if (pduBuf.size() != storedAdu.aduLen())
    {
        return;
    }

    server.onAduReceived(*this);

    reset();
}

void ModbusSession::respond(ModbusTcpAdu const& adu)
{
    PduBuffer buf;
    ModbusCodec codec(buf);
    codec.encode(adu);

    int rc = link->send(buf.begin(), buf.size());
    if (rc <= 0)
    {
        reset();
        server.removeSession(*this);
    }
}

void ModbusSession::onTimer()
{
}

} // namespace app
