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

    void close();

    void onSecureChannelEvent(OpcUaSecureChannelEvent const&);

private:
    OpcUaClientSecureChannel channel;
};

} // namespace app::ua
