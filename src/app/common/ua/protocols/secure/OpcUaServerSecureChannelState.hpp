#pragma once

#include "Logger.hpp"
#include "OpcUaConnection.hpp"

namespace app::ua
{

class OpcUaServerSecureChannel;

class OpcUaServerSecureChannelState
{
public:
    ~OpcUaServerSecureChannelState() {}

    virtual char const* name() const = 0;

    virtual void onConnected(OpcUaServerSecureChannel&) { LM(UA, LE, "Unexpected"); }

    virtual void onClosed(OpcUaServerSecureChannel&) { LM(UA, LE, "Unexpected"); }

    virtual void onDataReceived(OpcUaServerSecureChannel&, OpcUaConnection&) { LM(UA, LE, "Unexpected"); }

    virtual void onError(OpcUaServerSecureChannel&) { LM(UA, LE, "Unexpected"); }

    virtual void onEnter(OpcUaServerSecureChannel&) {}

    virtual void onExit(OpcUaServerSecureChannel&) {}

};

} // namespace app::ua
