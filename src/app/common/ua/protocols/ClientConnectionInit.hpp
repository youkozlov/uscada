#pragma once

#include "ClientConnectionState.hpp"

namespace app::ua
{

class ClientConnectionInit : public ClientConnectionState
{
public:
    ClientConnectionInit() {}

    char const* name() const final { return "ClientConnectionInit"; };

    void onConnect(ClientConnection&) final;
};

} // namespace app::ua
