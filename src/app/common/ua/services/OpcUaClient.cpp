#include "OpcUaClient.hpp"
#include "Logger.hpp"

namespace app::ua
{

OpcUaClient::OpcUaClient(reactor::ReactorInterface& reactor)
    : connection(reactor)
{
}

OpcUaClient::~OpcUaClient()
{
}

void OpcUaClient::connect(reactor::LinkAddr& addr)
{
    channel.setHandler([this](auto ev){ onSecureChannelEvent(ev); });
    connection.setHandler([&channel = channel](auto& ev){ channel.onConnectionEvent(ev); });
    connection.connect(addr);
}

void OpcUaClient::onSecureChannelEvent(OpcUaSecureChannelEvent ev)
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
