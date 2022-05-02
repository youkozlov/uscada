#include "ServerConnectionReceiveHello.hpp"
#include "ServerConnectionEstablished.hpp"
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
    case ServerConnection::Result::noerror:
    break;
    case ServerConnection::Result::done:
    {
        switch (fsm.sendAcknowledge())
        {
        case ServerConnection::Result::noerror:
        {
            LM(UA, LE, "Unexpected");
        }
        break;
        case ServerConnection::Result::done:
        {
            fsm.transit<ServerConnectionEstablished>();
        }
        break;
        case ServerConnection::Result::error:
        {
            fsm.closeLink();
            fsm.transit<ServerConnectionInit>();
        }
        break;
        }
    }
    break;
    case ServerConnection::Result::error:
    {
        fsm.closeLink();
        fsm.transit<ServerConnectionInit>();
    }
    break;
    }
}

void ServerConnectionReceiveHello::onTimer(ServerConnection& fsm)
{
    fsm.closeLink();
    fsm.transit<ServerConnectionInit>();
}

void ServerConnectionReceiveHello::onExit(ServerConnection& fsm)
{
    fsm.stopTimer();
}

} // namespace app::ua
