#pragma once

#include "ClientConnectionState.hpp"

namespace ua
{

class ClientConnectionConnecting : public ClientConnectionState
{
public:
    ClientConnectionConnecting() {}

    char const* name() const final { return "ClientConnectionConnecting"; };

    void onEnter(ClientConnection&) final;

    void onError(ClientConnection&) final;

    void onConnected(ClientConnection&) final;

    void onTimer(ClientConnection&) final;

    void onExit(ClientConnection&) final;
};

} // namespace ua
