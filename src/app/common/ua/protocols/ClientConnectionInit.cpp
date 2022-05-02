#include "ClientConnectionInit.hpp"
#include "ClientConnectionConnecting.hpp"
#include "ClientConnection.hpp"

namespace ua
{

void ClientConnectionInit::onConnect(ClientConnection& fsm)
{
    fsm.transit<ClientConnectionConnecting>();
}

} // namespace ua
