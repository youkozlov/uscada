#pragma once

#include "ClientConnectionState.hpp"

namespace app::ua
{

class ClientConnectionConnected : public ClientConnectionState
{
public:
    ClientConnectionConnected() {}

    char const* name() const final { return "ClientConnectionConnected"; };

    void onEnter(ClientConnection&) final;

    void onDataReceived(ClientConnection&) final;

    void onTimer(ClientConnection&) final;

    void onExit(ClientConnection&) final;
};

} // namespace app::ua
