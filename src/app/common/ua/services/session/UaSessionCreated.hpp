#pragma once

#include "UaSessionState.hpp"

namespace app::ua
{

class UaSessionCreated : public UaSessionState
{
public:
    UaSessionCreated() {}

    char const* name() const final { return "UaSessionCreated"; }

    void onActivate(UaSession&, UaActivateSessionReq const&, UaServiceHandler) final;

    void onClose(UaSession&, UaCloseSessionReq const&, UaServiceHandler) final;
};

} // namespace app::ua
