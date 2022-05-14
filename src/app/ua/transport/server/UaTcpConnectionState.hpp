#pragma once

#include "LinkPtr.hpp"
#include "Logger.hpp"
#include "MsgUaOpenSecureChannelRsp.hpp"
#include "MsgUaCloseSecureChannelRsp.hpp"
#include "MsgUaSecuredMessageSendReq.hpp"
#include "MsgUaConnectionReleaseReq.hpp"

namespace app::ua::transport
{

class UaTcpConnection;

class UaTcpConnectionState
{
public:
    ~UaTcpConnectionState() {}

    virtual char const* name() const = 0;

    virtual void onAcceptLink(UaTcpConnection&, reactor::LinkPtr&) { LM(UA, LE, "Unexpected"); }

    virtual void onReceive(UaTcpConnection&, MsgUaOpenSecureChannelRsp const&) { LM(UA, LE, "Unexpected"); }

    virtual void onReceive(UaTcpConnection&, MsgUaCloseSecureChannelRsp const&) { LM(UA, LE, "Unexpected"); }

    virtual void onReceive(UaTcpConnection&, MsgUaSecuredMessageSendReq const&) { LM(UA, LE, "Unexpected"); }

    virtual void onReceive(UaTcpConnection&, MsgUaConnectionReleaseReq const&) { LM(UA, LE, "Unexpected"); }

    virtual void onConnected(UaTcpConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onDataReceived(UaTcpConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onError(UaTcpConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onTimer(UaTcpConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onEnter(UaTcpConnection&) {}

    virtual void onExit(UaTcpConnection&) {}

};

} // namespace app::ua::transport
