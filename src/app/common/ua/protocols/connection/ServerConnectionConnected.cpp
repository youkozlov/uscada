#include "ServerConnectionConnected.hpp"
#include "ServerConnectionInit.hpp"
#include "ServerConnection.hpp"

namespace app::ua
{

void ServerConnectionConnected::onEnter(ServerConnection& fsm)
{
    fsm.notifyConnected();
    fsm.receivePreaction();
    fsm.startTimer(ServerConnection::establishTimeout);
}

void ServerConnectionConnected::onDataReceived(ServerConnection& fsm)
{
    switch (fsm.receive())
    {
    case OpcUaConnection::Result::noerror:
    break;
    case OpcUaConnection::Result::done:
    {
        fsm.notifyDataReceived();
        fsm.receivePreaction();
    }
    break;
    case OpcUaConnection::Result::error:
    {
        fsm.closeLink();
        fsm.notifyError();
        fsm.transit<ServerConnectionInit>();
    }
    break;
    }
}

void ServerConnectionConnected::onClose(ServerConnection& fsm)
{
    fsm.closeLink();
    fsm.transit<ServerConnectionInit>();
}

void ServerConnectionConnected::onTimer(ServerConnection& fsm)
{
    fsm.closeLink();
    fsm.notifyClosed();
    fsm.transit<ServerConnectionInit>();
}

void ServerConnectionConnected::onExit(ServerConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua
