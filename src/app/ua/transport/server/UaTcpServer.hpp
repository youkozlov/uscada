#pragma once

#include "ReactorInterface.hpp"
#include "ReleaserInterface.hpp"
#include "LinkAddr.hpp"
#include "AcceptorPtr.hpp"
#include "EntityId.hpp"
#include "UaTcpConnection.hpp"
#include "UaEntityPool.hpp"

namespace app::ua::transport
{

class UaTcpServer : public ReleaserInterface
{
public:
    explicit UaTcpServer(EntityId, reactor::ReactorInterface&);

    ~UaTcpServer();

    void receive(MsgUaOpenSecureChannelRsp const&);
    void receive(MsgUaCloseSecureChannelRsp const&);
    void receive(MsgUaSecuredMessageSendReq const&);
    void receive(MsgUaConnectionReleaseReq const&);

    void listen(reactor::LinkAddr const& addr);

private:
    void release(UaConnectionId) final;

    void onAcceptEvent();

    EntityId const uid;
    reactor::ReactorInterface& reactor;
    reactor::LinkAddr addr;
    reactor::AcceptorPtr acceptor;
    UaEntityPool<UaTcpConnection> connectionPool;
};

} // namespace app::ua::transport
