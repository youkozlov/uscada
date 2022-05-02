#include "ServerConnectionInit.hpp"
#include "ServerConnectionConnecting.hpp"
#include "ServerConnection.hpp"

namespace app::ua
{

void ServerConnectionInit::onConnect(ServerConnection& fsm)
{
    fsm.transit<ServerConnectionConnecting>();
}

} // namespace app::ua
