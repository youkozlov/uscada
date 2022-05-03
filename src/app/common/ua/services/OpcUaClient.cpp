#include "OpcUaClient.hpp"
#include "Logger.hpp"

namespace app::ua
{

OpcUaClient::OpcUaClient()
{
}

OpcUaClient::~OpcUaClient()
{
}

void OpcUaClient::connect(reactor::LinkAddr& addr)
{
    //channel.setHandler([this](auto ev){ onSecureChannelEvent(ev); });
    connection.setHandler([this](auto ev){ onConnectionEvent(ev); });
    connection.connect(addr);
}

void OpcUaClient::onConnectionEvent(OpcUaConnectionEvent ev)
{
    switch (ev)
    {
    case OpcUaConnectionEvent::connected:
        //channel.open(connection);
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

void OpcUaClient::onSecureChannelEvent(SecureChannelEvent ev)
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
