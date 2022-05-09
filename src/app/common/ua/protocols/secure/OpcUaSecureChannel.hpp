#pragma once

#include <functional>
#include "OpcUaConnection.hpp"
#include "EntityId.hpp"

namespace app::ua
{

class OpcUaSecureChannel;

struct OpcUaSecureChannelEvent
{
    enum Type
    {
          established
        , request
        , closed
        , error
    };
    Type type;
    OpcUaSecureChannel& channel;
};

using OpcUaSecureChannelHandler = std::function<void(OpcUaSecureChannelEvent const&)>;

class OpcUaSecureChannel
{
public:
    enum class Result
    {
          noerror
        , done
        , error
    };
    OpcUaSecureChannel(EntityId);

    ~OpcUaSecureChannel();

    void setHandler(OpcUaSecureChannelHandler);

    virtual void close() = 0;

    virtual OpcUaSduBuffer& getRxBuffer() = 0;

    virtual void send(OpcUaSduBuffer const&) = 0;

    EntityId getUid() const { return uid; }

protected:

    void notifyEstablished();

    void notifyDataReceived();

    void notifyClosed();

    void notifyError();

private:
    EntityId const uid;
    OpcUaSecureChannelHandler handler;
};

} // namespace app::ua
