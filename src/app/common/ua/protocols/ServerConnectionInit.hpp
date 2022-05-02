#pragma once

#include "ServerConnectionState.hpp"

namespace app::ua
{

class ServerConnectionInit : public ServerConnectionState
{
public:
    ServerConnectionInit() {}

    char const* name() const final { return "ServerConnectionInit"; };

    void onConnect(ServerConnection&) final;
};

} // namespace app::ua
