#pragma once

#include <functional>

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
    OpcUaSecureChannel();

    ~OpcUaSecureChannel();

protected:

    void setHandler(OpcUaSecureChannelHandler);

    void notifyEstablished();

    void notifyDataReceived();

    void notifyClosed();

    void notifyError();

private:
    OpcUaSecureChannelHandler handler;
};

} // namespace app::ua
