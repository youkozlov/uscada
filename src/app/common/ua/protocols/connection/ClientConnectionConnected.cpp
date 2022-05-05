#include "ClientConnectionConnected.hpp"
#include "ClientConnectionInit.hpp"
#include "ClientConnection.hpp"

namespace app::ua
{

void ClientConnectionConnected::onEnter(ClientConnection& fsm)
{
    fsm.notifyConnected();
    fsm.receivePreaction();
    fsm.startTimer(ClientConnection::establishTimeout);
}

void ClientConnectionConnected::onDataReceived(ClientConnection& fsm)
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
        fsm.transit<ClientConnectionInit>();
    }
    break;
    }
}

void ClientConnectionConnected::onClose(ClientConnection& fsm)
{
    fsm.closeLink();
    fsm.transit<ClientConnectionInit>();
}

void ClientConnectionConnected::onTimer(ClientConnection& fsm)
{
    fsm.closeLink();
    fsm.notifyClosed();
    fsm.transit<ClientConnectionInit>();
}

void ClientConnectionConnected::onExit(ClientConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua
