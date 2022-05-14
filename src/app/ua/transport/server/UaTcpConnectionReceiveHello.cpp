#include "UaTcpConnectionReceiveHello.hpp"
#include "UaTcpConnectionInit.hpp"
#include "UaTcpConnectionConnected.hpp"
#include "UaTcpConnection.hpp"
#include "UaTcpDefs.hpp"

namespace app::ua::transport
{

void UaTcpConnectionReceiveHello::onEnter(UaTcpConnection& fsm)
{
    fsm.startTimer(opcUaTcpReceiveTimeout);
    fsm.receivePreaction();
}

void UaTcpConnectionReceiveHello::onDataReceived(UaTcpConnection& fsm)
{
    switch (fsm.receiveHello())
    {
    case UaTcpConnection::Result::noerror:
    break;
    case UaTcpConnection::Result::done:
    {
        fsm.transit<UaTcpConnectionConnected>();
    }
    break;
    case UaTcpConnection::Result::error:
    {
        fsm.transit<UaTcpConnectionInit>();
    }
    break;
    }
}

void UaTcpConnectionReceiveHello::onTimer(UaTcpConnection& fsm)
{
    fsm.transit<UaTcpConnectionInit>();
}

void UaTcpConnectionReceiveHello::onExit(UaTcpConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua::transport
