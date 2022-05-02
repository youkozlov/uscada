#include "ClientConnectionEstablished.hpp"
#include "ClientConnectionInit.hpp"
#include "ClientConnection.hpp"

namespace ua
{

void ClientConnectionEstablished::onEnter(ClientConnection& fsm)
{
    fsm.startTimer(ClientConnection::establishTimeout);
}

void ClientConnectionEstablished::onDataReceived(ClientConnection&)
{
}

void ClientConnectionEstablished::onTimer(ClientConnection& fsm)
{
    fsm.closeLink();
    fsm.transit<ClientConnectionInit>();
}

void ClientConnectionEstablished::onExit(ClientConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace ua
