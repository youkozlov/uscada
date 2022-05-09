#pragma once

#include "UaSessionState.hpp"

namespace app::ua
{

class UaSessionInit : public UaSessionState
{
public:
    UaSessionInit() {}

    char const* name() const final { return "UaSessionInit"; }

    void onEnter(UaSession&) final;

    void onCreate(UaSession&, UaCreateSessionReq const&, UaServiceHandler) final;
};

} // namespace app::ua
