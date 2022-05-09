#pragma once

#include <optional>

#include "LinkPtr.hpp"
#include "TimerPtr.hpp"
#include "LinkInterface.hpp"
#include "LinkHandler.hpp"
#include "ReactorInterface.hpp"
#include "OpcUaSduBuffer.hpp"

namespace app::ua
{

class OpcUaConnection;
/*
struct OpcUaConnectionEvent
{
    enum Type
    {
          connected
        , data
        , closed
        , error
    };
    Type type;
    OpcUaConnection& connection;
};

using OpcUaConnectionHandler = std::function<void(OpcUaConnectionEvent const&)>;
*/

class OpcUaConnectionHandler
{
public:
    virtual ~OpcUaConnectionHandler() {}

    virtual void onConnectionConnectedEvent() = 0;

    virtual void onConnectionDataReceivedEvent() = 0;

    virtual void onConnectionErrorEvent() = 0;

    virtual void onConnectionClosedEvent() = 0;
};

class OpcUaConnection
{
public:
    enum class Result
    {
          noerror
        , done
        , error
    };

    explicit OpcUaConnection(reactor::ReactorInterface&, OpcUaConnectionHandler&);

    virtual ~OpcUaConnection();

    Result send(OpcUaSduBuffer const&);

    OpcUaSduBuffer& getRxBuffer() { return rx; }

protected:

    virtual void onLinkEvent(reactor::LinkEvent) = 0;

    virtual void onTimerEvent() = 0;

    void setLinkAddr(reactor::LinkAddr const&);

    void setLink(reactor::LinkPtr&);

    void allocLink();

    void allocTimer();

    void releaseResources();

    void connectLink();

    void closeLink();

    void receivePreaction();

    Result receive();

    void startTimer(long);

    void stopTimer();

    void notifyConnected();

    void notifyDataReceived();

    void notifyClosed();

    void notifyError();

private:
    reactor::ReactorInterface& reactor;
    reactor::LinkAddr addr;
    reactor::LinkPtr link;
    reactor::TimerPtr timer;
    OpcUaSduBuffer rx;
    OpcUaConnectionHandler& handler;
};

} // namespace app::ua
