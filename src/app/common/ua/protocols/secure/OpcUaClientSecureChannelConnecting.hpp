#pragma once

#include "OpcUaClientSecureChannelState.hpp"

namespace app::ua
{

class OpcUaClientSecureChannelConnecting : public OpcUaClientSecureChannelState
{
public:
    OpcUaClientSecureChannelConnecting() {}

    char const* name() const final { return "OpcUaClientSecureChannelConnecting"; }

    void onConnected(OpcUaClientSecureChannel&) final;

    void onClosed(OpcUaClientSecureChannel&) final;

    void onError(OpcUaClientSecureChannel&) final;
};

} // namespace app::ua
