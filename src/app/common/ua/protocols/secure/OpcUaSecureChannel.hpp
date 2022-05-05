#pragma once

#include <functional>
#include "OpcUaConnection.hpp"

namespace app::ua
{

enum class OpcUaSecureChannelEvent
{
      established
    , data
    , closed
    , error
};

using OpcUaSecureChannelHandler = std::function<void(OpcUaSecureChannelEvent)>;

class OpcUaSecureChannel
{
public:
    enum class Result
    {
          noerror
        , done
        , error
    };
    OpcUaSecureChannel();

    ~OpcUaSecureChannel();

    void setHandler(OpcUaSecureChannelHandler);

    void onConnectionEvent(OpcUaConnectionEvent const&);

protected:

    virtual void onConnected(OpcUaConnection&) = 0;

    virtual void onDataReceived(OpcUaConnection&) = 0;

    virtual void onError() = 0;

    virtual void onClosed() = 0;

    void notifyEstablished();

    void notifyDataReceived();

    void notifyClosed();

    void notifyError();

private:
    OpcUaSecureChannelHandler handler;
};

} // namespace app::ua
