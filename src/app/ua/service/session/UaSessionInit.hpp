#pragma once

#include "UaSessionState.hpp"

namespace app::ua::service
{

class UaSessionInit : public UaSessionState
{
public:
    UaSessionInit() {}

    char const* name() const final { return "UaSessionInit"; }

    void onEnter(UaSession&) final;

    void onReceive(UaSession&, UaEncodedMessageHdr const&, UaCreateSessionReq const&) final;
};

} // namespace app::ua::service
