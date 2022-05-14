#pragma once

#include "MsgUaTransportConfigReq.hpp"
#include "MsgUaOpenSecureChannelRsp.hpp"
#include "MsgUaCloseSecureChannelRsp.hpp"
#include "MsgUaSecuredMessageSendReq.hpp"
#include "MsgUaConnectionReleaseReq.hpp"
#include "UaEntityPool.hpp"
#include "UaTcpServer.hpp"

namespace app::ua::transport
{

class UaTransport
{
public:
    UaTransport();

    ~UaTransport();

    void receive(MsgUaTransportConfigReq const&);
    void receive(MsgUaOpenSecureChannelRsp const&);
    void receive(MsgUaCloseSecureChannelRsp const&);
    void receive(MsgUaSecuredMessageSendReq const&);
    void receive(MsgUaConnectionReleaseReq const&);

private:
    UaTcpServer server;
};

} // namespace app::ua::transport
