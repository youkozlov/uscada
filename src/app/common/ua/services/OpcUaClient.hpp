#pragma once

#include "ClientConnection.hpp"
#include "OpcUaClientSecureChannel.hpp"

namespace app::ua
{

class OpcUaClient
{
public:
    OpcUaClient(reactor::ReactorInterface&);

    ~OpcUaClient();

    void connect(reactor::LinkAddr&);

    void onSecureChannelEvent(OpcUaSecureChannelEvent);

private:
    ClientConnection connection;
    OpcUaClientSecureChannel channel;
};

} // namespace app::ua
