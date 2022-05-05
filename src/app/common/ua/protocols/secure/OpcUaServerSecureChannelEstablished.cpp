#include "OpcUaServerSecureChannelEstablished.hpp"
#include "OpcUaServerSecureChannelInit.hpp"
#include "OpcUaServerSecureChannel.hpp"

namespace app::ua
{

void OpcUaServerSecureChannelEstablished::onEnter(OpcUaServerSecureChannel&)
{
}

void OpcUaServerSecureChannelEstablished::onDataReceived(OpcUaServerSecureChannel& fsm, OpcUaConnection& connection)
{
}

void OpcUaServerSecureChannelEstablished::onClosed(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyClosed();
    fsm.transit<OpcUaServerSecureChannelInit>();
}

void OpcUaServerSecureChannelEstablished::onError(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyError();
    fsm.transit<OpcUaServerSecureChannelInit>();
}

} // namespace app::ua
