#pragma once

#include "ServerConnectionState.hpp"

namespace ua
{

class ServerConnectionEstablished : public ServerConnectionState
{
public:
    ServerConnectionEstablished() {}

    char const* name() const final { return "ServerConnectionEstablished"; };

    void onEnter(ServerConnection&) final;

    void onDataReceived(ServerConnection&) final;

    void onTimer(ServerConnection&) final;

    void onExit(ServerConnection&) final;
};

} // namespace ua
