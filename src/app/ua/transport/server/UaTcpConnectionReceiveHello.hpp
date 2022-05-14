#pragma once

#include "UaTcpConnectionState.hpp"

namespace app::ua::transport
{

class UaTcpConnectionReceiveHello : public UaTcpConnectionState
{
public:
    UaTcpConnectionReceiveHello() {}

    char const* name() const final { return "UaTcpConnectionReceiveHello"; }

    void onEnter(UaTcpConnection&) final;

    void onDataReceived(UaTcpConnection&) final;

    void onTimer(UaTcpConnection&) final;

    void onExit(UaTcpConnection&) final;
};

} // namespace app::ua::transport
