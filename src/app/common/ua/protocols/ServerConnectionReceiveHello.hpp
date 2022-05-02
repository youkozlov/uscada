#pragma once

#include "ServerConnectionState.hpp"

namespace ua
{

class ServerConnectionReceiveHello : public ServerConnectionState
{
public:
    ServerConnectionReceiveHello() {}

    char const* name() const final { return "ServerConnectionReceiveHello"; };

    void onEnter(ServerConnection&) final;

    void onDataReceived(ServerConnection&) final;

    void onTimer(ServerConnection&) final;

    void onExit(ServerConnection&) final;
};

} // namespace ua
