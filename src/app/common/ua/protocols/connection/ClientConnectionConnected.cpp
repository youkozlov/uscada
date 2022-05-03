#include "ClientConnectionConnected.hpp"
#include "ClientConnectionInit.hpp"
#include "ClientConnection.hpp"

namespace app::ua
{

void ClientConnectionConnected::onEnter(ClientConnection& fsm)
{
    fsm.startTimer(ClientConnection::establishTimeout);
}

void ClientConnectionConnected::onDataReceived(ClientConnection&)
{
}

void ClientConnectionConnected::onTimer(ClientConnection& fsm)
{
    fsm.closeLink();
    fsm.transit<ClientConnectionInit>();
}

void ClientConnectionConnected::onExit(ClientConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua
