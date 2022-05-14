#pragma once

#include "FsmBase.hpp"
#include "UaControllerState.hpp"

#include "MsgControllerStartReq.hpp"
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

class UaController : public app::FsmBase<UaController, UaControllerState>
{
public:
    explicit UaController();

    ~UaController();

    void receive(MsgControllerStartReq const&);
    void receive(MsgControllerStopReq const&);
    void receive(MsgUaSecureChannelInitRsp const&);
    void receive(MsgUaSecureChannelConfigRsp const&);
    void receive(MsgUaSecureChannelReleaseRsp const&);
    void receive(MsgUaTransportInitRsp const&);
    void receive(MsgUaTransportConfigRsp const&);
    void receive(MsgUaTransportReleaseRsp const&);
    void receive(MsgUaServiceInitRsp const&);
    void receive(MsgUaServiceConfigRsp const&);
    void receive(MsgUaServiceReleaseRsp const&);

private:
};

} // namespace app::controller
