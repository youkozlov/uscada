#include "ServerConnectionConnecting.hpp"
#include "ServerConnectionReceiveHello.hpp"
#include "ServerConnectionInit.hpp"
#include "ServerConnection.hpp"

namespace app::ua
{

void ServerConnectionConnecting::onEnter(ServerConnection& fsm)
{
    fsm.connectLink();
    fsm.startTimer(ServerConnection::connectTimeout);
}

void ServerConnectionConnecting::onConnected(ServerConnection& fsm)
{
    switch (fsm.sendReverseHello())
    {
    case OpcUaConnection::Result::noerror:
    {
        LM(UA, LE, "Unexpected");
    }
    break;
    case OpcUaConnection::Result::done:
    {
        fsm.transit<ServerConnectionReceiveHello>();
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

void ServerConnectionConnecting::onError(ServerConnection& fsm)
{
    LM(UA, LW, "onError");
    fsm.notifyError();
    fsm.transit<ServerConnectionInit>();
}

void ServerConnectionConnecting::onTimer(ServerConnection& fsm)
{
    LM(UA, LW, "onTimer");
    fsm.closeLink();
    fsm.notifyError();
    fsm.transit<ServerConnectionInit>();
}

void ServerConnectionConnecting::onExit(ServerConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua
