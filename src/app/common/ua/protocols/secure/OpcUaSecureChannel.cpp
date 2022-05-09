#include "OpcUaSecureChannel.hpp"

namespace app::ua
{

OpcUaSecureChannel::OpcUaSecureChannel(EntityId uid_)
    : uid(uid_)
{
}

OpcUaSecureChannel::~OpcUaSecureChannel()
{
}

void OpcUaSecureChannel::setHandler(OpcUaSecureChannelHandler handler_)
{
    handler = handler_;
}

void OpcUaSecureChannel::notifyEstablished()
{
    if (handler)
        handler({OpcUaSecureChannelEvent::established, *this});
}

void OpcUaSecureChannel::notifyDataReceived()
{
    if (handler)
        handler({OpcUaSecureChannelEvent::request, *this});
}

void OpcUaSecureChannel::notifyClosed()
{
    if (handler)
        handler({OpcUaSecureChannelEvent::closed, *this});
}

void OpcUaSecureChannel::notifyError()
{
    if (handler)
        handler({OpcUaSecureChannelEvent::error, *this});
}

} // namespace app::ua
