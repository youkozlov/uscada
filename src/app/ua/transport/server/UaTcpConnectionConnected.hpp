#pragma once

#include "UaTcpConnectionState.hpp"

namespace app::ua::transport
{

class UaTcpConnectionConnected : public UaTcpConnectionState
{
public:
    UaTcpConnectionConnected() {}

    char const* name() const final { return "UaTcpConnectionConnected"; }

    void onEnter(UaTcpConnection&) final;

    void onDataReceived(UaTcpConnection&) final;

    void onReceive(UaTcpConnection&, MsgUaOpenSecureChannelRsp const&) final;

    void onReceive(UaTcpConnection&, MsgUaCloseSecureChannelRsp const&) final;

    void onReceive(UaTcpConnection&, MsgUaSecuredMessageSendReq const&) final;

    void onReceive(UaTcpConnection&, MsgUaConnectionReleaseReq const&) final;

    void onTimer(UaTcpConnection&) final;

    void onExit(UaTcpConnection&) final;
};

} // namespace app::ua::transport
