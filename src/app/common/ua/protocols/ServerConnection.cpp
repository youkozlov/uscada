#include "ServerConnection.hpp"
#include "LinkInterface.hpp"
#include "TimerInterface.hpp"
#include "ServerConnectionInit.hpp"

namespace ua
{

ServerConnection::ServerConnection(reactor::ReactorInterface& reactor)
    : FsmBase(&app::getSingleton<ServerConnectionInit>())
    , link(reactor.createLink([this](auto ev){ onLinkEvent(ev); }))
    , timer(reactor.createTimer([this](){ onTimerEvent(); }))

{
}

ServerConnection::~ServerConnection()
{
}

void ServerConnection::connect()
{
    getState().onConnect(*this);
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

void ServerConnection::connectLink()
{
    reactor::LinkAddr addr;
    link->connect(addr);
}

void ServerConnection::closeLink()
{
    link->close();
}

ServerConnection::Result ServerConnection::sendReverseHello()
{
    OpcUaBinaryCodec tx;

    ReverseHelloMessage revHello;
    MessageHeader hdr;
    tx << hdr << revHello;

    auto const payloadSize = tx.size() - messageHeaderSize;

    setPayloadSizeToHdr(tx.begin(), payloadSize);

    LM(UA, LD, "ServerConnection-0, sendReverseHello, payloadSize/pktSize: %u/%u", payloadSize, tx.size());

    int rc = link->send(tx.begin(), tx.size());
    if (rc <= 0)
    {
        LM(UA, LI, "ServerConnection-0, send return: %d", rc);
        return Result::error;
    }
    return Result::done;
}

void ServerConnection::receivePreaction()
{
    codec.reset();
}

ServerConnection::Result ServerConnection::receiveHello()
{
    // TODO REMOVE
    if (codec.size() > 1024)
    {
        LM(UA, LW, "ServerConnection-0, received packet is invalid");
        return Result::error;
    }

    int rc = link->receive(codec.end(), codec.capacity());

    if (rc <= 0)
    {
        LM(UA, LI, "ServerConnection-0, receive return: %d", rc);
        return Result::error;
    }

    codec.seek(rc);

    if (codec.size() < messageHeaderSize)
    {
        return Result::noerror;
    }

    if (codec.size() < getMsgSizeFromHdr(codec.begin()))
    {
        return Result::noerror;
    }

    if (codec.size() != getMsgSizeFromHdr(codec.begin()))
    {
        LM(UA, LW, "ServerConnection-0, received packet is invalid");
        return Result::error;
    }

    auto const pktSize = codec.size();

    MessageHeader hdr;
    HelloMessage hello;
    codec >> hdr >> hello;

    LM(UA, LD, "ServerConnection-0, receiveHello, pkt size(%u)", pktSize);

    return Result::done;
}

ServerConnection::Result ServerConnection::sendAcknowledge()
{
    OpcUaBinaryCodec tx;

    AcknowledgeMessage ack;
    MessageHeader hdr;
    tx << hdr << ack;

    setPayloadSizeToHdr(tx.begin(), tx.size() - messageHeaderSize);

    LM(UA, LD, "ServerConnection-0, sendAcknowledge, pkt size(%u)", tx.size());

    int rc = link->send(tx.begin(), tx.size());
    if (rc <= 0)
    {
        LM(UA, LI, "ServerConnection-0, send return: %d", rc);
        return Result::error;
    }
    return Result::done;
}

void ServerConnection::startTimer(long timeout)
{
    timer->start(timeout);
}

void ServerConnection::stopTimer()
{
    timer->stop();
}

} // namespace ua
