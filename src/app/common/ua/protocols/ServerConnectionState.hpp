#pragma once

#include "Logger.hpp"

namespace app::ua
{

class ServerConnection;

class ServerConnectionState
{
public:
    ~ServerConnectionState() {}

    virtual char const* name() const = 0;

    virtual void onConnect(ServerConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onConnected(ServerConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onDataReceived(ServerConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onError(ServerConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onTimer(ServerConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onEnter(ServerConnection&) {}

    virtual void onExit(ServerConnection&) {}

};

} // namespace app::ua
