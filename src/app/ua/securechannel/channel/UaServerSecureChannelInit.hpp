#pragma once

#include "UaServerSecureChannelState.hpp"

namespace app::ua::securechannel
{

class UaServerSecureChannelInit : public UaServerSecureChannelState
{
public:
    UaServerSecureChannelInit() {}

    char const* name() const final { return "UaServerSecureChannelInit"; }

    void onEnter(UaServerSecureChannel&) final;

    void onReceive(UaServerSecureChannel&, MsgUaOpenSecureChannelReq const&) final;
};

} // namespace app::ua::securechannel
