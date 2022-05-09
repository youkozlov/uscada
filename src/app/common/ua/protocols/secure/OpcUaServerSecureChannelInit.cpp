#include "OpcUaServerSecureChannelInit.hpp"
#include "OpcUaServerSecureChannelConnecting.hpp"
#include "OpcUaServerSecureChannel.hpp"

namespace app::ua
{

void OpcUaServerSecureChannelInit::onOpen(OpcUaServerSecureChannel& fsm, reactor::LinkPtr& link)
{
    fsm.acceptConnection(link);
    fsm.transit<OpcUaServerSecureChannelConnecting>();
}

} // namespace app::ua
