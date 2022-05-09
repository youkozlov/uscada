#pragma once

#include "OpcUaClientSecureChannelState.hpp"

namespace app::ua
{

class OpcUaClientSecureChannelReceiveOpenRsp : public OpcUaClientSecureChannelState
{
public:
    OpcUaClientSecureChannelReceiveOpenRsp() {}

    char const* name() const final { return "OpcUaClientSecureChannelReceiveOpenRsp"; }

    void onDataReceived(OpcUaClientSecureChannel&) final;

    void onClosed(OpcUaClientSecureChannel&) final;

    void onError(OpcUaClientSecureChannel&) final;
};

} // namespace app::ua
