#pragma once

#include "OpcUaClientSecureChannelState.hpp"

namespace app::ua
{

class OpcUaClientSecureChannelEstablished : public OpcUaClientSecureChannelState
{
public:
    OpcUaClientSecureChannelEstablished() {}

    char const* name() const final { return "OpcUaClientSecureChannelEstablished"; }

    void onEnter(OpcUaClientSecureChannel&) final;

    void onDataReceived(OpcUaClientSecureChannel&) final;

    void onClosed(OpcUaClientSecureChannel&) final;

    void onError(OpcUaClientSecureChannel&) final;
};

} // namespace app::ua
