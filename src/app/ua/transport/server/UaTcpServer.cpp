#include "UaTcpServer.hpp"
#include "Logger.hpp"

namespace app::ua::transport
{

UaTcpServer::UaTcpServer(EntityId uid_, reactor::ReactorInterface& reactor_)
    : uid(uid_)
    , reactor(reactor_)
    , connectionPool("UaTcpConnection", reactor_, *this)
{
}

UaTcpServer::~UaTcpServer()
{
}

void UaTcpServer::receive(MsgUaOpenSecureChannelRsp const& msg)
{
    auto& connection = connectionPool.get(msg.connectionId);
    connection.getState().onReceive(connection, msg);
}

void UaTcpServer::receive(MsgUaCloseSecureChannelRsp const& msg)
{
    auto& connection = connectionPool.get(msg.connectionId);
    connection.getState().onReceive(connection, msg);
}

void UaTcpServer::receive(MsgUaSecuredMessageSendReq const& msg)
{
    auto& connection = connectionPool.get(msg.connectionId);
    connection.getState().onReceive(connection, msg);
}

void UaTcpServer::receive(MsgUaConnectionReleaseReq const& msg)
{
    auto& connection = connectionPool.get(msg.connectionId);
    connection.getState().onReceive(connection, msg);
}

void UaTcpServer::listen(reactor::LinkAddr const& addr)
{
    acceptor = reactor.createAcceptor([this](){ onAcceptEvent(); });
    acceptor->listen(addr);
}

void UaTcpServer::release(UaConnectionId connectionId)
{
    connectionPool.release(connectionId);
}

void UaTcpServer::onAcceptEvent()
{
    LM(UATL, LD, "Uid=%u, onAcceptEvent", uid);

    auto link = reactor.createLink({});
    acceptor->accept(*link);

    EntityId connectionId;
    if (not connectionPool.alloc(connectionId))
    {
        LM(UATL, LD, "Uid=%u, Can not alloc tcp connection", uid);
        return;
    }
    auto& connection = connectionPool.get(connectionId);
    connection.getState().onAcceptLink(connection, link);
}

} // namespace app::ua::transport
