#include "ServerConnectionReceiveHello.hpp"
#include "ServerConnectionConnected.hpp"
#include "ServerConnectionInit.hpp"
#include "ServerConnection.hpp"

namespace app::ua
{

void ServerConnectionReceiveHello::onEnter(ServerConnection& fsm)
{
    fsm.startTimer(ServerConnection::receiveTimeout);
    fsm.receivePreaction();
}

void ServerConnectionReceiveHello::onDataReceived(ServerConnection& fsm)
{
    switch (fsm.receiveHello())
    {
    case OpcUaConnection::Result::noerror:
    break;
    case OpcUaConnection::Result::done:
    {
        switch (fsm.sendAcknowledge())
        {
        case OpcUaConnection::Result::noerror:
        {
            LM(UA, LE, "Unexpected");
        }
        break;
        case OpcUaConnection::Result::done:
        {
            fsm.transit<ServerConnectionConnected>();
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

void ServerConnectionReceiveHello::onTimer(ServerConnection& fsm)
{
    LM(UA, LW, "onTimer");
    fsm.closeLink();
    fsm.notifyError();
    fsm.transit<ServerConnectionInit>();
}

void ServerConnectionReceiveHello::onExit(ServerConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua
