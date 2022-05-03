#pragma once

#include "OpcUaServerSecureChannel.hpp"
#include "ServerConnection.hpp"
#include "AcceptorPtr.hpp"

namespace app::ua
{

class OpcUaServer
{
public:
    OpcUaServer();

    ~OpcUaServer();

    void listen(reactor::LinkAddr& addr);

    void onAcceptEvent();

    void onConnectionEvent(OpcUaConnectionEvent);

    void onSecureChannelEvent(SecureChannelEvent);

private:
    reactor::AcceptorPtr acceptor;
    ServerConnection connection;
    OpcUaServerSecureChannel channel;
};

} // namespace app::ua
