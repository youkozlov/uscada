#pragma once

#include "ClientConnectionState.hpp"

namespace app::ua
{

class ClientConnectionEstablished : public ClientConnectionState
{
public:
    ClientConnectionEstablished() {}

    char const* name() const final { return "ClientConnectionEstablished"; };

    void onEnter(ClientConnection&) final;

    void onDataReceived(ClientConnection&) final;

    void onTimer(ClientConnection&) final;

    void onExit(ClientConnection&) final;
};

} // namespace app::ua
