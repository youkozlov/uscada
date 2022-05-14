#pragma once

#include "UaControllerState.hpp"

namespace app::controller
{

class UaControllerInit : public UaControllerState
{
public:
    UaControllerInit() {}

    char const* name() const final { return "UaControllerInit"; }

    void onReceive(UaController&, MsgControllerStartReq const&) final;
};

} // namespace app::controller
