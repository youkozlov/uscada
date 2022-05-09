#pragma once

#include "OpcUaClientSecureChannelState.hpp"

namespace app::ua
{

class OpcUaClientSecureChannelInit : public OpcUaClientSecureChannelState
{
public:
    OpcUaClientSecureChannelInit() {}

    char const* name() const final { return "OpcUaClientSecureChannelInit"; }

    void onOpen(OpcUaClientSecureChannel&, reactor::LinkAddr&) final;

};

} // namespace app::ua
