#pragma once

#include "ServerConnectionState.hpp"

namespace app::ua
{

class ServerConnectionConnected : public ServerConnectionState
{
public:
    ServerConnectionConnected() {}

    char const* name() const final { return "ServerConnectionConnected"; };

    void onEnter(ServerConnection&) final;

    void onDataReceived(ServerConnection&) final;

    void onClose(ServerConnection&) final;

    void onTimer(ServerConnection&) final;

    void onExit(ServerConnection&) final;
};

} // namespace app::ua
