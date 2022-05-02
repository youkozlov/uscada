#pragma once

#include "ClientConnectionState.hpp"

namespace ua
{

class ClientConnectionInit : public ClientConnectionState
{
public:
    ClientConnectionInit() {}

    char const* name() const final { return "ClientConnectionInit"; };

    void onConnect(ClientConnection&) final;
};

} // namespace ua
