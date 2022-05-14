#pragma once

#include "Logger.hpp"
#include "MsgUaOpenSecureChannelReq.hpp"
#include "MsgUaCloseSecureChannelReq.hpp"
#include "MsgUaAssociateSecureChannelReq.hpp"
#include "MsgUaSecuredMessageReceiveInd.hpp"
#include "MsgUaConnectionReleaseInd.hpp"
#include "MsgUaEncodedMessageSendReq.hpp"

namespace app::ua::securechannel
{

class UaServerSecureChannel;

class UaServerSecureChannelState
{
public:
    ~UaServerSecureChannelState() {}

    virtual char const* name() const = 0;

    virtual void onReceive(UaServerSecureChannel&, MsgUaOpenSecureChannelReq const&) { LM(UASC, LE, "Unexpected"); }

    virtual void onReceive(UaServerSecureChannel&, MsgUaCloseSecureChannelReq const&) { LM(UASC, LE, "Unexpected"); }

    virtual void onReceive(UaServerSecureChannel&, MsgUaAssociateSecureChannelReq const&) { LM(UASC, LE, "Unexpected"); }

    virtual void onReceive(UaServerSecureChannel&, MsgUaSecuredMessageReceiveInd const&) { LM(UASC, LE, "Unexpected"); }

    virtual void onReceive(UaServerSecureChannel&, MsgUaConnectionReleaseInd const&) { LM(UASC, LE, "Unexpected"); }

    virtual void onReceive(UaServerSecureChannel&, MsgUaEncodedMessageSendReq const&) { LM(UASC, LE, "Unexpected"); }

    virtual void onEnter(UaServerSecureChannel&) {}

    virtual void onExit(UaServerSecureChannel&) {}

};

} // namespace app::ua::securechannel
