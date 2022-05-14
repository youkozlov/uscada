#pragma once

#include "UaSessionState.hpp"

namespace app::ua::service
{

class UaSessionCreated : public UaSessionState
{
public:
    UaSessionCreated() {}

    char const* name() const final { return "UaSessionCreated"; }

    void onReceive(UaSession&, UaEncodedMessageHdr const&, UaActivateSessionReq const&) final;

    void onReceive(UaSession&, UaEncodedMessageHdr const&, UaCloseSessionReq const&) final;
};

} // namespace app::ua::service
