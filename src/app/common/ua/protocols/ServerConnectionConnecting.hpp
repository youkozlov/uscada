#pragma once

#include "ServerConnectionState.hpp"

namespace app::ua
{

class ServerConnectionConnecting : public ServerConnectionState
{
public:
    ServerConnectionConnecting() {}

    char const* name() const final { return "ServerConnectionConnecting"; };

    void onEnter(ServerConnection&) final;

    void onError(ServerConnection&) final;

    void onConnected(ServerConnection&) final;

    void onTimer(ServerConnection&) final;

    void onExit(ServerConnection&) final;
};

} // namespace app::ua
