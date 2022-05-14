#pragma once

#include "UaTcpConnectionState.hpp"

namespace app::ua::transport
{

class UaTcpConnectionInit : public UaTcpConnectionState
{
public:
    UaTcpConnectionInit() {}

    char const* name() const final { return "UaTcpConnectionInit"; }

    void onEnter(UaTcpConnection&) final;

    void onAcceptLink(UaTcpConnection&, reactor::LinkPtr&) final;
};

} // namespace app::ua::transport
