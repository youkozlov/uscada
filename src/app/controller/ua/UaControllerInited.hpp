#pragma once

#include "UaControllerState.hpp"

namespace app::controller
{

class UaControllerInited : public UaControllerState
{
public:
    UaControllerInited() {}

    char const* name() const final { return "UaControllerInited"; }

    void onReceive(UaController&, MsgUaSecureChannelInitRsp const&) final;

    void onReceive(UaController&, MsgUaTransportInitRsp const&) final;

    void onReceive(UaController&, MsgUaServiceInitRsp const&) final;

    void onReceive(UaController&, MsgControllerStopReq const&) final;
};

} // namespace app::controller
