#include "ServerConnectionEstablished.hpp"
#include "ServerConnectionInit.hpp"
#include "ServerConnection.hpp"

namespace ua
{

void ServerConnectionEstablished::onEnter(ServerConnection& fsm)
{
    fsm.startTimer(ServerConnection::establishTimeout);
}

void ServerConnectionEstablished::onDataReceived(ServerConnection&)
{
}

void ServerConnectionEstablished::onTimer(ServerConnection& fsm)
{
    fsm.closeLink();
    fsm.transit<ServerConnectionInit>();
}

void ServerConnectionEstablished::onExit(ServerConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace ua
