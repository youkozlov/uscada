#pragma once

#include "OpcUaServerSecureChannelState.hpp"

namespace app::ua
{

class OpcUaServerSecureChannelInit : public OpcUaServerSecureChannelState
{
public:
    OpcUaServerSecureChannelInit() {}

    char const* name() const final { return "OpcUaServerSecureChannelInit"; }

    void onConnected(OpcUaServerSecureChannel&) final;

    void onClosed(OpcUaServerSecureChannel&) final;

    void onError(OpcUaServerSecureChannel&) final;
};

} // namespace app::ua
