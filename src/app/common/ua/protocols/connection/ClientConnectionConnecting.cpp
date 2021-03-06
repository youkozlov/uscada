#include "ClientConnectionConnecting.hpp"
#include "ClientConnectionReceiveAck.hpp"
#include "ClientConnectionInit.hpp"
#include "ClientConnection.hpp"

namespace app::ua
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
    case OpcUaConnection::Result::noerror:
    {
        LM(UA, LE, "Unexpected");
        fsm.notifyError();
    }
    break;
    case OpcUaConnection::Result::done:
    {
        fsm.transit<ClientConnectionReceiveAck>();
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

void ClientConnectionConnecting::onError(ClientConnection& fsm)
{
    LM(UA, LW, "onError");
    fsm.notifyError();
    fsm.transit<ClientConnectionInit>();
}

void ClientConnectionConnecting::onTimer(ClientConnection& fsm)
{
    LM(UA, LW, "onTimer");
    fsm.closeLink();
    fsm.notifyError();
    fsm.transit<ClientConnectionInit>();
}

void ClientConnectionConnecting::onExit(ClientConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua
