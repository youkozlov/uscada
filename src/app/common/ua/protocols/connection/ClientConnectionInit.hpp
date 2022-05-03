#pragma once

#include "ClientConnectionState.hpp"

namespace app::ua
{

class ClientConnectionInit : public ClientConnectionState
{
public:
    ClientConnectionInit() {}

    char const* name() const final { return "ClientConnectionInit"; };

    void onEnter(ClientConnection&) final;

    void onConnect(ClientConnection&, reactor::LinkAddr const&) final;

    void onExit(ClientConnection&) final;
};

} // namespace app::ua
