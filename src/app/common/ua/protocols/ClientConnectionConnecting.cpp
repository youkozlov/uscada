#include "ClientConnectionConnecting.hpp"
#include "ClientConnectionReceiveAck.hpp"
#include "ClientConnectionInit.hpp"
#include "ClientConnection.hpp"

namespace ua
{

void ClientConnectionConnecting::onEnter(ClientConnection& fsm)
{
    fsm.connectLink();
    fsm.startTimer(ClientConnection::connectTimeout);
}

void ClientConnectionConnecting::onConnected(ClientConnection& fsm)
{
    switch (fsm.sendHello())
    {
    case ClientConnection::Result::noerror:
    {
        LM(UA, LE, "Unexpected");
    }
    break;
    case ClientConnection::Result::done:
    {
        fsm.transit<ClientConnectionReceiveAck>();
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

void ClientConnectionConnecting::onError(ClientConnection& fsm)
{
    LM(UA, LW, "onError");
    fsm.transit<ClientConnectionInit>();
}

void ClientConnectionConnecting::onTimer(ClientConnection& fsm)
{
    LM(UA, LW, "onTimer");
    fsm.closeLink();
    fsm.transit<ClientConnectionInit>();
}

void ClientConnectionConnecting::onExit(ClientConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace ua
