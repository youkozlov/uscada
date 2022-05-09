#include "OpcUaClientSecureChannelEstablished.hpp"
#include "OpcUaClientSecureChannelInit.hpp"
#include "OpcUaClientSecureChannel.hpp"

namespace app::ua
{

void OpcUaClientSecureChannelEstablished::onEnter(OpcUaClientSecureChannel&)
{
}

void OpcUaClientSecureChannelEstablished::onDataReceived(OpcUaClientSecureChannel&)
{
}

void OpcUaClientSecureChannelEstablished::onClosed(OpcUaClientSecureChannel& fsm)
{
    fsm.notifyClosed();
    fsm.transit<OpcUaClientSecureChannelInit>();
}

void OpcUaClientSecureChannelEstablished::onError(OpcUaClientSecureChannel& fsm)
{
    fsm.notifyError();
    fsm.transit<OpcUaClientSecureChannelInit>();
}

} // namespace app::ua
