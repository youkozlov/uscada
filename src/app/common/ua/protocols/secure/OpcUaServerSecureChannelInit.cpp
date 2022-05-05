#include "OpcUaServerSecureChannelInit.hpp"
#include "OpcUaServerSecureChannelReceiveOpenReq.hpp"
#include "OpcUaServerSecureChannel.hpp"

namespace app::ua
{

void OpcUaServerSecureChannelInit::onConnected(OpcUaServerSecureChannel& fsm)
{
    fsm.transit<OpcUaServerSecureChannelReceiveOpenReq>();
}

void OpcUaServerSecureChannelInit::onClosed(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyClosed();
}

void OpcUaServerSecureChannelInit::onError(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyError();
}

} // namespace app::ua
