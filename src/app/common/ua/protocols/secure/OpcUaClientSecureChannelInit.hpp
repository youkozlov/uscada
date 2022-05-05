#pragma once

#include "OpcUaClientSecureChannelState.hpp"

namespace app::ua
{

class OpcUaClientSecureChannelInit : public OpcUaClientSecureChannelState
{
public:
    OpcUaClientSecureChannelInit() {}

    char const* name() const final { return "OpcUaClientSecureChannelInit"; }

    void onConnected(OpcUaClientSecureChannel&, OpcUaConnection&) final;

    void onClosed(OpcUaClientSecureChannel&) final;

    void onError(OpcUaClientSecureChannel&) final;
};

} // namespace app::ua
