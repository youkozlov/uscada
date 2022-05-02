#pragma once

#include "ClientConnectionState.hpp"

namespace ua
{

class ClientConnectionReceiveAck : public ClientConnectionState
{
public:
    ClientConnectionReceiveAck() {}

    char const* name() const final { return "ClientConnectionReceiveAck"; };

    void onEnter(ClientConnection&) final;

    void onDataReceived(ClientConnection&) final;

    void onTimer(ClientConnection&) final;

    void onExit(ClientConnection&) final;
};

} // namespace ua
