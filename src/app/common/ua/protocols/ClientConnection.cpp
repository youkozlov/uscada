#include "ClientConnection.hpp"
#include "LinkInterface.hpp"
#include "TimerInterface.hpp"
#include "ClientConnectionInit.hpp"

namespace ua
{

ClientConnection::ClientConnection(reactor::ReactorInterface& reactor)
    : FsmBase(&app::getSingleton<ClientConnectionInit>())
    , link(reactor.createLink([this](auto ev){ onLinkEvent(ev); }))
    , timer(reactor.createTimer([this](){ onTimerEvent(); }))

{
}

ClientConnection::~ClientConnection()
{
}

void ClientConnection::connect()
{
    getState().onConnect(*this);
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

void ClientConnection::connectLink()
{
    reactor::LinkAddr addr;
    link->connect(addr);
}

void ClientConnection::closeLink()
{
    link->close();
}

void ClientConnection::receivePreaction()
{
    codec.reset();
}

ClientConnection::Result ClientConnection::receiveAck()
{
    // TODO REMOVE
    if (codec.size() > 1024)
    {
        LM(UA, LW, "ClientConnection-0, received packet is invalid");
        return Result::error;
    }

    int rc = link->receive(codec.end(), codec.capacity());

    if (rc <= 0)
    {
        LM(UA, LI, "ClientConnection-0, receive return: %d", rc);
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
        LM(UA, LW, "ClientConnection-0, received packet is invalid");
        return Result::error;
    }

    auto const pktSize = codec.size();

    MessageHeader hdr;
    AcknowledgeMessage hello;
    codec >> hdr >> hello;

    LM(UA, LD, "ClientConnection-0, receiveAck, pkt size(%u)", pktSize);

    return Result::done;
}

ClientConnection::Result ClientConnection::sendHello()
{
    OpcUaBinaryCodec tx;

    HelloMessage ack;
    MessageHeader hdr;
    tx << hdr << ack;

    setPayloadSizeToHdr(tx.begin(), tx.size() - messageHeaderSize);

    LM(UA, LD, "ClientConnection-0, sendHello, pkt size(%u)", tx.size());

    int rc = link->send(tx.begin(), tx.size());
    if (rc <= 0)
    {
        LM(UA, LI, "ClientConnection-0, send return: %d", rc);
        return Result::error;
    }
    return Result::done;
}

void ClientConnection::startTimer(long timeout)
{
    timer->start(timeout);
}

void ClientConnection::stopTimer()
{
    timer->stop();
}

} // namespace ua
