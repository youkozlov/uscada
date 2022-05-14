#include "UaTcpConnectionInit.hpp"
#include "UaTcpConnectionReceiveHello.hpp"
#include "UaTcpConnection.hpp"

namespace app::ua::transport
{

void UaTcpConnectionInit::onEnter(UaTcpConnection& fsm)
{
    fsm.release();
}

void UaTcpConnectionInit::onAcceptLink(UaTcpConnection& fsm, reactor::LinkPtr& link)
{
    fsm.acceptLink(link);
    fsm.allocTimer();
    fsm.transit<UaTcpConnectionReceiveHello>();
}

} // namespace app::ua::transport
