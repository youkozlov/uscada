#include "OpcUaServerSecureChannelConnecting.hpp"
#include "OpcUaServerSecureChannelReceiveOpenReq.hpp"
#include "OpcUaServerSecureChannelInit.hpp"
#include "OpcUaServerSecureChannel.hpp"

namespace app::ua
{

void OpcUaServerSecureChannelConnecting::onConnected(OpcUaServerSecureChannel& fsm)
{
    fsm.transit<OpcUaServerSecureChannelReceiveOpenReq>();
}

void OpcUaServerSecureChannelConnecting::onClosed(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyClosed();
    fsm.transit<OpcUaServerSecureChannelInit>();
}

void OpcUaServerSecureChannelConnecting::onError(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyError();
    fsm.transit<OpcUaServerSecureChannelInit>();
}

} // namespace app::ua
