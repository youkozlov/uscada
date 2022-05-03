#pragma once

#include "ClientConnection.hpp"

namespace app::ua
{

class OpcUaClient
{
public:
    OpcUaClient();

    ~OpcUaClient();

    void connect(reactor::LinkAddr&);

    void onConnectionEvent(OpcUaConnectionEvent);

    void onSecureChannelEvent(SecureChannelEvent);

private:
    ClientConnection connection;
    OpcUaClientSecureChannel channel;
};

} // namespace app::ua
