#pragma once

#include "Logger.hpp"
#include "OpcUaConnection.hpp"

namespace app::ua
{

class OpcUaClientSecureChannel;

class OpcUaClientSecureChannelState
{
public:
    ~OpcUaClientSecureChannelState() {}

    virtual char const* name() const = 0;

    virtual void onConnected(OpcUaClientSecureChannel&) { LM(UA, LE, "Unexpected"); }

    virtual void onOpen(OpcUaClientSecureChannel&, reactor::LinkAddr&) { LM(UA, LE, "Unexpected"); }

    virtual void onClosed(OpcUaClientSecureChannel&) { LM(UA, LE, "Unexpected"); }

    virtual void onDataReceived(OpcUaClientSecureChannel&) { LM(UA, LE, "Unexpected"); }

    virtual void onError(OpcUaClientSecureChannel&) { LM(UA, LE, "Unexpected"); }

    virtual void onEnter(OpcUaClientSecureChannel&) {}

    virtual void onExit(OpcUaClientSecureChannel&) {}

};

} // namespace app::ua
