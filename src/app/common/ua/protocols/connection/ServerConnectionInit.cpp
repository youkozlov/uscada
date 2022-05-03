#include "ServerConnectionInit.hpp"
#include "ServerConnectionConnecting.hpp"
#include "ServerConnectionReceiveHello.hpp"
#include "ServerConnection.hpp"

namespace app::ua
{

void ServerConnectionInit::onEnter(ServerConnection& fsm)
{
    fsm.releaseResources();
}

void ServerConnectionInit::onConnect(ServerConnection& fsm, reactor::LinkAddr const& addr)
{
    fsm.setLinkAddr(addr);
    fsm.allocLink();
    fsm.allocTimer();
    fsm.transit<ServerConnectionConnecting>();
}

void ServerConnectionInit::onAccept(ServerConnection& fsm, reactor::LinkPtr& link)
{
    fsm.setLink(link);
    fsm.allocTimer();
    fsm.transit<ServerConnectionReceiveHello>();
}

void ServerConnectionInit::onExit(ServerConnection&)
{
}

} // namespace app::ua
