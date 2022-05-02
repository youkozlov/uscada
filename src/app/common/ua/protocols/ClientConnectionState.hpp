#pragma once

#include "Logger.hpp"

namespace app::ua
{

class ClientConnection;

class ClientConnectionState
{
public:
    ~ClientConnectionState() {}

    virtual char const* name() const = 0;

    virtual void onConnect(ClientConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onConnected(ClientConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onDataReceived(ClientConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onError(ClientConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onTimer(ClientConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onEnter(ClientConnection&) {}

    virtual void onExit(ClientConnection&) {}

};

} // namespace app::ua
