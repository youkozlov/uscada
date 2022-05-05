#include "ServerConnection.hpp"
#include "ConnectionProtocolCodec.hpp"
#include "LinkInterface.hpp"
#include "TimerInterface.hpp"
#include "ServerConnectionInit.hpp"
#include "ServerConnectionReceiveHello.hpp"
#include "OpcUaProtocolDefs.hpp"

namespace app::ua
{

ServerConnection::ServerConnection(reactor::ReactorInterface& reactor_)
    : FsmBase(&app::getSingleton<ServerConnectionInit>())
    , OpcUaConnection(reactor_)
{
}

ServerConnection::~ServerConnection()
{
}

void ServerConnection::connect(reactor::LinkAddr const& addr)
{
    getState().onConnect(*this, addr);
}

void ServerConnection::accept(reactor::LinkPtr& link)
{
    getState().onAccept(*this, link);
}

void ServerConnection::close()
{
    getState().onClose(*this);
}

void ServerConnection::onLinkEvent(reactor::LinkEvent ev)
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

void ServerConnection::onTimerEvent()
{
    getState().onTimer(*this);
}

ServerConnection::Result ServerConnection::sendReverseHello()
{
    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);

    MessageHeader hdr;
    hdr.messageType[0] = 'R';
    hdr.messageType[1] = 'H';
    hdr.messageType[2] = 'E';
    hdr.isFinal = 'F';
    ReverseHelloMessage revHello;
    codec << hdr << revHello;

    setPayloadSizeToHdr(tx.begin(), tx.size());

    LM(UA, LD, "ServerConnection-0, sendReverseHello, size(%u)", tx.size());

    return OpcUaConnection::send(tx);
}

OpcUaConnection::Result ServerConnection::receiveHello()
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

    if (not isMsgHello(getRxBuffer().begin()))
    {
        LM(UA, LW, "ServerConnection-0, unexpected packet type");
        return Result::error;
    }

    OpcUaBinaryCodec codec(getRxBuffer());

    MessageHeader hdr;
    HelloMessage hello;
    codec >> hdr >> hello;

    LM(UA, LD, "ServerConnection-0, received HelloMessage");

    return OpcUaConnection::Result::done;
}

OpcUaConnection::Result ServerConnection::sendAcknowledge()
{
    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);

    MessageHeader hdr;
    hdr.messageType[0] = 'A';
    hdr.messageType[1] = 'C';
    hdr.messageType[2] = 'K';
    hdr.isFinal = 'F';
    codec << hdr;

    AcknowledgeMessage ack;
    ack.protocolVersion = opcUaProtocolVersion;
    codec << ack;

    setPayloadSizeToHdr(tx.begin(), tx.size());

    LM(UA, LD, "ServerConnection-0, send AcknowledgeMessage, size(%u)", tx.size());

    return OpcUaConnection::send(tx);
}

} // namespace app::ua
