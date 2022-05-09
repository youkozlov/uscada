#include "OpcUaConnection.hpp"
#include "MessageHeader.hpp"
#include "Logger.hpp"

namespace app::ua
{

OpcUaConnection::OpcUaConnection(reactor::ReactorInterface& reactor_, OpcUaConnectionHandler& handler_)
    : reactor(reactor_)
    , handler(handler_)
{
}

OpcUaConnection::~OpcUaConnection()
{
}

void OpcUaConnection::setLinkAddr(reactor::LinkAddr const& addr_)
{
    addr = addr_;
}

void OpcUaConnection::setLink(reactor::LinkPtr& link_)
{
    link = std::move(link_);
    link->setHandler([this](auto ev){ onLinkEvent(ev); });
}

void OpcUaConnection::allocLink()
{
    link = reactor.createLink([this](auto ev){ onLinkEvent(ev); });
}

void OpcUaConnection::allocTimer()
{
    timer = reactor.createTimer([this](){ onTimerEvent(); });
}

void OpcUaConnection::releaseResources()
{
    link.reset();
    timer.reset();
}

void OpcUaConnection::connectLink()
{
    link->connect(addr);
}

void OpcUaConnection::closeLink()
{
    link->close();
}

OpcUaConnection::Result OpcUaConnection::send(OpcUaSduBuffer const& tx)
{
    int rc = link->send(tx.begin(), tx.size());
    if (rc <= 0)
    {
        LM(UA, LI, "send return: %d", rc);
        return Result::error;
    }
    return Result::done;
}

void OpcUaConnection::receivePreaction()
{
    rx.reset();
}

OpcUaConnection::Result OpcUaConnection::receive()
{
    // TODO REMOVE MN
    if (rx.size() > 1024)
    {
        LM(UA, LW, "Received packet is invalid");
        return Result::error;
    }

    auto const& result = link->receive(rx.end(), rx.capacity());
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

    rx.seek(result.len);

    if (rx.size() < messageHeaderSize)
    {
        return Result::noerror;
    }

    if (rx.size() < getMsgSizeFromHdr(rx.begin()))
    {
        return Result::noerror;
    }

    if (rx.size() != getMsgSizeFromHdr(rx.begin()))
    {
        LM(UA, LW, "Packet has invalid size");
        return Result::error;
    }

    return Result::done;
}

void OpcUaConnection::startTimer(long timeout)
{
    timer->start(timeout);
}

void OpcUaConnection::stopTimer()
{
    timer->stop();
}

void OpcUaConnection::notifyConnected()
{
    handler.onConnectionConnectedEvent();
}

void OpcUaConnection::notifyDataReceived()
{
    handler.onConnectionDataReceivedEvent();
}

void OpcUaConnection::notifyClosed()
{
    handler.onConnectionClosedEvent();
}

void OpcUaConnection::notifyError()
{
    handler.onConnectionErrorEvent();
}

} // namespace app::ua
