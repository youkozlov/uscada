#pragma once

#include "ServerConnectionState.hpp"

namespace app::ua
{

class ServerConnectionInit : public ServerConnectionState
{
public:
    ServerConnectionInit() {}

    char const* name() const final { return "ServerConnectionInit"; };

    void onEnter(ServerConnection&) final;

    void onConnect(ServerConnection&, reactor::LinkAddr const&) final;

    void onAccept(ServerConnection&, reactor::LinkPtr&) final;

    void onExit(ServerConnection&) final;
};

} // namespace app::ua
