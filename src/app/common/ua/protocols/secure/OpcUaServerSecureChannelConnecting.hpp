#pragma once

#include "OpcUaServerSecureChannelState.hpp"

namespace app::ua
{

class OpcUaServerSecureChannelConnecting : public OpcUaServerSecureChannelState
{
public:
    OpcUaServerSecureChannelConnecting() {}

    char const* name() const final { return "OpcUaServerSecureChannelConnecting"; }

    void onConnected(OpcUaServerSecureChannel&) final;

    void onClosed(OpcUaServerSecureChannel&) final;

    void onError(OpcUaServerSecureChannel&) final;
};

} // namespace app::ua
