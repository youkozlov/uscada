#include "OpcUaServer.hpp"

namespace app::ua
{

OpcUaServer::OpcUaServer(/* args */)
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

    //channel.setHandler([this](auto ev){ onSecureChannelEvent(ev); });
    connection.setHandler([this](auto ev){ onConnectionEvent(ev); });

    auto link = reactor.createLink([this](auto ev){ connection.onLinkEvent(ev); });
    acceptor->accept(*link);
    connection.accept(link);
}

void OpcUaServer::onConnectionEvent(OpcUaConnectionEvent ev)
{
    switch (ev)
    {
    case OpcUaConnectionEvent::connected:
    break;
    case OpcUaConnectionEvent::data:
        //channel.processData(connection);
    break;
    case OpcUaConnectionEvent::error:
    break;
    case OpcUaConnectionEvent::closed:
    break;
    }
}

void OpcUaServer::onSecureChannelEvent(SecureChannelEvent ev)
{
    switch (ev)
    {
    case SecureChannelEvent::established:
    break;
    case SecureChannelEvent::data:
    break;
    case SecureChannelEvent::error:
    break;
    }
}

} // namespace app::ua
