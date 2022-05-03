#pragma once

#include "LinkPtr.hpp"
#include "TimerPtr.hpp"
#include "LinkInterface.hpp"
#include "LinkHandler.hpp"
#include "ReactorInterface.hpp"
#include "OpcUaSduBuffer.hpp"

namespace app::ua
{

enum class OpcUaConnectionEvent
{
      connected
    , data
    , closed
    , error
};

using OpcUaConnectionHandler = std::function<void(OpcUaConnectionEvent)>;

class OpcUaConnection
{
public:
    enum class Result
    {
          noerror
        , done
        , error
    };

    explicit OpcUaConnection(reactor::ReactorInterface&);

    virtual ~OpcUaConnection();

    OpcUaSduBuffer& getRxBuffer() { return rx; }

protected:

    virtual void onLinkEvent(reactor::LinkEvent) = 0;

    virtual void onTimerEvent() = 0;

    void setHandler(OpcUaConnectionHandler);

    void setLinkAddr(reactor::LinkAddr const&);

    void setLink(reactor::LinkPtr&);

    void allocLink();

    void allocTimer();

    void releaseResources();

    void connectLink();

    void closeLink();

    Result send(OpcUaSduBuffer const&);

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
    OpcUaConnectionHandler handler;
};

} // namespace app::ua
