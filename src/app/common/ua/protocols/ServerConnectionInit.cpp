#include "ServerConnectionInit.hpp"
#include "ServerConnectionConnecting.hpp"
#include "ServerConnection.hpp"

namespace ua
{

void ServerConnectionInit::onConnect(ServerConnection& fsm)
{
    fsm.transit<ServerConnectionConnecting>();
}

} // namespace ua
