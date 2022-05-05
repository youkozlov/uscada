#include "OpcUaSecureChannel.hpp"

namespace app::ua
{

OpcUaSecureChannel::OpcUaSecureChannel()
{
}

OpcUaSecureChannel::~OpcUaSecureChannel()
{
}

void OpcUaSecureChannel::setHandler(OpcUaSecureChannelHandler handler_)
{
    handler = handler_;
}

void OpcUaSecureChannel::onConnectionEvent(OpcUaConnectionEvent const& ev)
{
    switch (ev.type)
    {
    case OpcUaConnectionEvent::connected:
        onConnected(ev.connection);
    break;
    case OpcUaConnectionEvent::data:
        onDataReceived(ev.connection);
    break;
    case OpcUaConnectionEvent::error:
        onError();
    break;
    case OpcUaConnectionEvent::closed:
        onClosed();
    break;
    }
}

void OpcUaSecureChannel::notifyEstablished()
{
    if (handler)
        handler(OpcUaSecureChannelEvent::established);
}

void OpcUaSecureChannel::notifyDataReceived()
{
    if (handler)
        handler(OpcUaSecureChannelEvent::data);
}

void OpcUaSecureChannel::notifyClosed()
{
    if (handler)
        handler(OpcUaSecureChannelEvent::closed);
}

void OpcUaSecureChannel::notifyError()
{
    if (handler)
        handler(OpcUaSecureChannelEvent::error);
}

} // namespace app::ua
