#include "ClientConnectionReceiveAck.hpp"
#include "ClientConnectionConnected.hpp"
#include "ClientConnectionInit.hpp"
#include "ClientConnection.hpp"

namespace app::ua
{

void ClientConnectionReceiveAck::onEnter(ClientConnection& fsm)
{
    fsm.startTimer(ClientConnection::receiveTimeout);
    fsm.receivePreaction();
}

void ClientConnectionReceiveAck::onDataReceived(ClientConnection& fsm)
{
    switch (fsm.receiveAck())
    {
    case OpcUaConnection::Result::noerror:
    break;
    case OpcUaConnection::Result::done:
    {
        fsm.transit<ClientConnectionConnected>();
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

void ClientConnectionReceiveAck::onTimer(ClientConnection& fsm)
{
    fsm.closeLink();
    fsm.notifyError();
    fsm.transit<ClientConnectionInit>();
}

void ClientConnectionReceiveAck::onExit(ClientConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua
