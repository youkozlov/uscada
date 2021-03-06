#pragma once

#include "OpcUaServerSecureChannelState.hpp"

namespace app::ua
{

class OpcUaServerSecureChannelReceiveOpenReq : public OpcUaServerSecureChannelState
{
public:
    OpcUaServerSecureChannelReceiveOpenReq() {}

    char const* name() const final { return "OpcUaServerSecureChannelReceiveOpenReq"; }

    void onOpenSecureChannelReq(OpcUaServerSecureChannel&) final;

    void onClosed(OpcUaServerSecureChannel&) final;

    void onError(OpcUaServerSecureChannel&) final;
};

} // namespace app::ua
