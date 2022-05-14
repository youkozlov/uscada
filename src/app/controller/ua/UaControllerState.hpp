#pragma once

#include "Logger.hpp"

#include "MsgControllerStartReq.hpp"
#include "MsgControllerStopReq.hpp"
#include "MsgUaSecureChannelInitRsp.hpp"
#include "MsgUaSecureChannelConfigRsp.hpp"
#include "MsgUaSecureChannelReleaseRsp.hpp"
#include "MsgUaTransportInitRsp.hpp"
#include "MsgUaTransportConfigRsp.hpp"
#include "MsgUaTransportReleaseRsp.hpp"
#include "MsgUaServiceInitRsp.hpp"
#include "MsgUaServiceConfigRsp.hpp"
#include "MsgUaServiceReleaseRsp.hpp"

namespace app::controller
{

class UaController;

class UaControllerState
{
public:
    ~UaControllerState() {}

    virtual char const* name() const = 0;

    virtual void onReceive(UaController&, MsgControllerStartReq const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onReceive(UaController&, MsgControllerStopReq const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onReceive(UaController&, MsgUaSecureChannelInitRsp const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onReceive(UaController&, MsgUaSecureChannelConfigRsp const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onReceive(UaController&, MsgUaSecureChannelReleaseRsp const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onReceive(UaController&, MsgUaTransportInitRsp const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onReceive(UaController&, MsgUaTransportConfigRsp const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onReceive(UaController&, MsgUaTransportReleaseRsp const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onReceive(UaController&, MsgUaServiceInitRsp const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onReceive(UaController&, MsgUaServiceConfigRsp const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onReceive(UaController&, MsgUaServiceReleaseRsp const&) { LM(CTRL, LE, "Unexpected"); }
    virtual void onEnter(UaController&) {}
    virtual void onExit(UaController&) {}
};

} // namespace app::controller
