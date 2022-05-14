#pragma once

#include "UaSessionState.hpp"

namespace app::ua::service
{

class UaSessionActivated : public UaSessionState
{
public:
    UaSessionActivated() {}

    char const* name() const final { return "UaSessionActivated"; }

    void onReceive(UaSession&, UaEncodedMessageHdr const&, UaActivateSessionReq const&) final;

    void onReceive(UaSession&, UaEncodedMessageHdr const&, UaCloseSessionReq const&) final;

    void onReceive(UaSession&, UaEncodedMessageHdr const&, UaServiceHandler const&) final;
};

} // namespace app::ua::service
