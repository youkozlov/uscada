#include "ClientConnectionInit.hpp"
#include "ClientConnectionConnecting.hpp"
#include "ClientConnection.hpp"

namespace app::ua
{

void ClientConnectionInit::onEnter(ClientConnection& fsm)
{
    fsm.releaseResources();
}

void ClientConnectionInit::onConnect(ClientConnection& fsm, reactor::LinkAddr const& addr)
{
    fsm.setLinkAddr(addr);
    fsm.allocLink();
    fsm.allocTimer();
    fsm.transit<ClientConnectionConnecting>();
}

void ClientConnectionInit::onExit(ClientConnection&)
{
}

} // namespace app::ua
