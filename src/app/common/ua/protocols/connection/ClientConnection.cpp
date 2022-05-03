#include "ClientConnection.hpp"
#include "ConnectionProtocolCodec.hpp"
#include "LinkInterface.hpp"
#include "TimerInterface.hpp"
#include "ClientConnectionInit.hpp"

namespace app::ua
{

ClientConnection::ClientConnection(reactor::ReactorInterface& reactor_)
    : FsmBase(&app::getSingleton<ClientConnectionInit>())
    , OpcUaConnection(reactor_)
{
}

ClientConnection::~ClientConnection()
{
}

void ClientConnection::connect(reactor::LinkAddr const& addr)
{
    getState().onConnect(*this, addr);
}

void ClientConnection::close()
{
    getState().onClose(*this);
}

void ClientConnection::onLinkEvent(reactor::LinkEvent ev)
{
    switch (ev)
    {
    case reactor::LinkEvent::connected:
        getState().onConnected(*this);
    break;
    case reactor::LinkEvent::data:
        getState().onDataReceived(*this);
    break;
    case reactor::LinkEvent::error:
        getState().onError(*this);
    break;
    }
}

void ClientConnection::onTimerEvent()
{
    getState().onTimer(*this);
}

OpcUaConnection::Result ClientConnection::receiveAck()
{
    switch (OpcUaConnection::receive())
    {
    case OpcUaConnection::Result::noerror:
    {
        return OpcUaConnection::Result::noerror;
    }
    break;
    case OpcUaConnection::Result::done:
    break;
    case OpcUaConnection::Result::error:
    {
        return OpcUaConnection::Result::error;
    }
    break;
    }

    if (not isMsgAck(getRxBuffer().begin()))
    {
        LM(UA, LW, "ClientConnection-0, unexpected packet type");
        return OpcUaConnection::Result::error;

    }

    OpcUaBinaryCodec codec(getRxBuffer());

    MessageHeader hdr;
    AcknowledgeMessage hello;
    codec >> hdr >> hello;

    LM(UA, LD, "ClientConnection-0, received AcknowledgeMessage");

    return OpcUaConnection::Result::done;
}

ClientConnection::Result ClientConnection::sendHello()
{
    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);

    HelloMessage ack;
    MessageHeader hdr;
    hdr.messageType[0] = 'H';
    hdr.messageType[1] = 'E';
    hdr.messageType[2] = 'L';
    hdr.reserved[0] = 'F';
    codec << hdr << ack;

    setPayloadSizeToHdr(tx.begin(), tx.size());

    LM(UA, LD, "ClientConnection-0, send HelloMessage, pkt size(%u)", tx.size());

    return OpcUaConnection::send(tx);
}

} // namespace app::ua
