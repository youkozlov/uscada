#pragma once

#include "FsmBase.hpp"
#include "ServerConnection.hpp"
#include "OpcUaSecureChannel.hpp"

namespace app::ua
{

class OpcUaServerSecureChannel : public app::FsmBase<OpcUaServerSecureChannel, OpcUaServerSecureChannelState>
                               , public OpcUaSecureChannel
{
public:
    using SecureChannelHandler = std::function<void()>;

    OpcUaServerSecureChannel();

    ~OpcUaServerSecureChannel();

    void processData(ServerConnection&);

private:
    OpcUaSecureChannelHandler handler;
};

} // namespace app::ua
