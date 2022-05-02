#include "ClientConnectionInit.hpp"
#include "ClientConnectionConnecting.hpp"
#include "ClientConnection.hpp"

namespace app::ua
{

void ClientConnectionInit::onConnect(ClientConnection& fsm)
{
    fsm.transit<ClientConnectionConnecting>();
}

} // namespace app::ua
