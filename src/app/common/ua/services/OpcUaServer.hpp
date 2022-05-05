#pragma once

#include "OpcUaServerSecureChannel.hpp"
#include "ServerConnection.hpp"
#include "AcceptorPtr.hpp"

namespace app::ua
{

class OpcUaServer
{
public:
    OpcUaServer(reactor::ReactorInterface&);

    ~OpcUaServer();

    void listen(reactor::LinkAddr& addr);

    void onAcceptEvent();

    void onSecureChannelEvent(OpcUaSecureChannelEvent);

private:
    reactor::ReactorInterface& reactor;
    reactor::AcceptorPtr acceptor;
    ServerConnection connection;
    OpcUaServerSecureChannel channel;
};

} // namespace app::ua
