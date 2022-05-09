#pragma once

#include "OpcUaServerSecureChannelState.hpp"

namespace app::ua
{

class OpcUaServerSecureChannelEstablished : public OpcUaServerSecureChannelState
{
public:
    OpcUaServerSecureChannelEstablished() {}

    char const* name() const final { return "OpcUaServerSecureChannelEstablished"; }

    void onOpenSecureChannelReq(OpcUaServerSecureChannel&) final;

    void onCloseSecureChannelReq(OpcUaServerSecureChannel&) final;

    void onSecureChannelReq(OpcUaServerSecureChannel&) final;

    void onClosed(OpcUaServerSecureChannel&) final;

    void onError(OpcUaServerSecureChannel&) final;
};

} // namespace app::ua
