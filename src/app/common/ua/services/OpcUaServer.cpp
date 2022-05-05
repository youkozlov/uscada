#include "OpcUaServer.hpp"

namespace app::ua
{

OpcUaServer::OpcUaServer(reactor::ReactorInterface& reactor_)
    : reactor(reactor_)
    , connection(reactor)
{
}

OpcUaServer::~OpcUaServer()
{
}

void OpcUaServer::listen(reactor::LinkAddr& addr)
{
    acceptor = reactor.createAcceptor([this](){ onAcceptEvent(); });
    acceptor->listen(addr);
}

void OpcUaServer::onAcceptEvent()
{
    LM(UA, LD, "onAcceptEvent");

    channel.setHandler([this](auto ev){ onSecureChannelEvent(ev); });
    connection.setHandler([&channel = channel](auto& ev){ channel.onConnectionEvent(ev); });

    auto link = reactor.createLink([this](auto ev){ connection.onLinkEvent(ev); });
    acceptor->accept(*link);
    connection.accept(link);
}

void OpcUaServer::onSecureChannelEvent(OpcUaSecureChannelEvent ev)
{
    switch (ev)
    {
    case OpcUaSecureChannelEvent::established:
        LM(UA, LD, "onSecureChannelEvent, established");
    break;
    case OpcUaSecureChannelEvent::data:
        LM(UA, LD, "onSecureChannelEvent, data");
    break;
    case OpcUaSecureChannelEvent::closed:
        LM(UA, LD, "onSecureChannelEvent, closed");
    break;
    case OpcUaSecureChannelEvent::error:
        LM(UA, LD, "onSecureChannelEvent, error");
    break;
    }
}

} // namespace app::ua
