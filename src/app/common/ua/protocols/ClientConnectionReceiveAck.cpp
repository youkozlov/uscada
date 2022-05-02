#include "ClientConnectionReceiveAck.hpp"
#include "ClientConnectionEstablished.hpp"
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
    case ClientConnection::Result::noerror:
    break;
    case ClientConnection::Result::done:
    {
        fsm.transit<ClientConnectionEstablished>();
    }
    break;
    case ClientConnection::Result::error:
    {
        fsm.closeLink();
        fsm.transit<ClientConnectionInit>();
    }
    break;
    }
}

void ClientConnectionReceiveAck::onTimer(ClientConnection& fsm)
{
    fsm.closeLink();
    fsm.transit<ClientConnectionInit>();
}

void ClientConnectionReceiveAck::onExit(ClientConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua
