#pragma once

#include "OpcUaServerSecureChannelState.hpp"

namespace app::ua
{

class OpcUaServerSecureChannelInit : public OpcUaServerSecureChannelState
{
public:
    OpcUaServerSecureChannelInit() {}

    char const* name() const final { return "OpcUaServerSecureChannelInit"; }

    void onOpen(OpcUaServerSecureChannel&, reactor::LinkPtr&) final;
};

} // namespace app::ua
