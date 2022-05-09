#include "OpcUaClientSecureChannelInit.hpp"
#include "OpcUaClientSecureChannelConnecting.hpp"
#include "OpcUaClientSecureChannel.hpp"

namespace app::ua
{

void OpcUaClientSecureChannelInit::onOpen(OpcUaClientSecureChannel& fsm, reactor::LinkAddr& addr)
{
    fsm.connectLink(addr);
    fsm.transit<OpcUaClientSecureChannelConnecting>();
}

} // namespace app::ua
