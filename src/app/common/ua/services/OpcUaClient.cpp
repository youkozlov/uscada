#include "OpcUaClient.hpp"
#include "Logger.hpp"

namespace app::ua
{

OpcUaClient::OpcUaClient(reactor::ReactorInterface& reactor)
    : channel(0, reactor)
{
}

OpcUaClient::~OpcUaClient()
{
}

void OpcUaClient::connect(reactor::LinkAddr& addr)
{
    channel.setHandler([this](auto const& ev){ onSecureChannelEvent(ev); });
    channel.open(addr);
}

void OpcUaClient::close()
{
    channel.close();
}

void OpcUaClient::onSecureChannelEvent(OpcUaSecureChannelEvent const& ev)
{
    switch (ev.type)
    {
    case OpcUaSecureChannelEvent::established:
        LM(UA, LD, "onSecureChannelEvent, established");
    break;
    case OpcUaSecureChannelEvent::request:
        LM(UA, LD, "onSecureChannelEvent, request");
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
