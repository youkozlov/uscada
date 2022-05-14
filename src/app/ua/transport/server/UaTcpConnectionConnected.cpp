#include "UaTcpConnectionConnected.hpp"
#include "UaTcpConnectionInit.hpp"
#include "UaTcpConnection.hpp"
#include "UaTcpDefs.hpp"

namespace app::ua::transport
{

void UaTcpConnectionConnected::onEnter(UaTcpConnection& fsm)
{
    fsm.startTimer(opcUaTcpReceiveTimeout);
    fsm.receivePreaction();
}

void UaTcpConnectionConnected::onDataReceived(UaTcpConnection& fsm)
{
    switch (fsm.receiveSecuredMessage())
    {
    case UaTcpConnection::Result::noerror:
    break;
    case UaTcpConnection::Result::done:
    {
        fsm.startTimer(opcUaTcpReceiveTimeout);
        fsm.receivePreaction();
    }
    break;
    case UaTcpConnection::Result::error:
    {
        fsm.sendUaConnectionReleaseInd();
        fsm.transit<UaTcpConnectionInit>();
    }
    break;
    }
}

void UaTcpConnectionConnected::onReceive(UaTcpConnection& fsm, MsgUaOpenSecureChannelRsp const& req)
{
    switch (fsm.receive(req))
    {
    case UaTcpConnection::Result::done:
    {}
    break;
    case UaTcpConnection::Result::noerror:
    case UaTcpConnection::Result::error:
    {
        fsm.sendUaConnectionReleaseInd();
        fsm.transit<UaTcpConnectionInit>();
    }
    break;
    }
}

void UaTcpConnectionConnected::onReceive(UaTcpConnection& fsm, MsgUaCloseSecureChannelRsp const& req)
{
    switch (fsm.receive(req))
    {
    case UaTcpConnection::Result::done:
    {}
    break;
    case UaTcpConnection::Result::noerror:
    case UaTcpConnection::Result::error:
    {
        fsm.sendUaConnectionReleaseInd();
        fsm.transit<UaTcpConnectionInit>();
    }
    break;
    }
}

void UaTcpConnectionConnected::onReceive(UaTcpConnection& fsm, MsgUaSecuredMessageSendReq const& req)
{
    switch (fsm.receive(req))
    {
    case UaTcpConnection::Result::done:
    {}
    break;
    case UaTcpConnection::Result::noerror:
    case UaTcpConnection::Result::error:
    {
        fsm.sendUaConnectionReleaseInd();
        fsm.transit<UaTcpConnectionInit>();
    }
    break;
    }
}

void UaTcpConnectionConnected::onReceive(UaTcpConnection& fsm, MsgUaConnectionReleaseReq const&)
{
    fsm.transit<UaTcpConnectionInit>();
}

void UaTcpConnectionConnected::onTimer(UaTcpConnection& fsm)
{
    fsm.sendUaConnectionReleaseInd();
    fsm.transit<UaTcpConnectionInit>();
}

void UaTcpConnectionConnected::onExit(UaTcpConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua::transport
