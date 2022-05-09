#pragma once

#include "UaSessionState.hpp"

namespace app::ua
{

class UaSessionActivated : public UaSessionState
{
public:
    UaSessionActivated() {}

    char const* name() const final { return "UaSessionActivated"; }

    void onClose(UaSession&, UaCloseSessionReq const&, UaServiceHandler) final;
};

} // namespace app::ua
