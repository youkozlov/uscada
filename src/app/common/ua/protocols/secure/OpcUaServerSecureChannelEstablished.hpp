#pragma once

#include "OpcUaServerSecureChannelState.hpp"

namespace app::ua
{

class OpcUaServerSecureChannelEstablished : public OpcUaServerSecureChannelState
{
public:
    OpcUaServerSecureChannelEstablished() {}

    char const* name() const final { return "OpcUaServerSecureChannelEstablished"; }

    void onEnter(OpcUaServerSecureChannel&) final;

    void onDataReceived(OpcUaServerSecureChannel&, OpcUaConnection&) final;

    void onClosed(OpcUaServerSecureChannel&) final;

    void onError(OpcUaServerSecureChannel&) final;
};

} // namespace app::ua
