#pragma once

#include "FsmBase.hpp"
#include "ReactorInterface.hpp"
#include "ServerConnectionState.hpp"
#include "LinkPtr.hpp"
#include "TimerPtr.hpp"
#include "ConnectionProtocolCodec.hpp"

namespace ua
{

class ServerConnectionInit;
class ServerConnectionConnecting;
class ServerConnectionReceiveHello;
class ServerConnectionEstablished;

class ServerConnection : public app::FsmBase<ServerConnection, ServerConnectionState>
{
public:
    enum class Result
    {
          noerror
        , done
        , error
    };

    ServerConnection(reactor::ReactorInterface&);

    ~ServerConnection();

    char const* name() const { return "OpcUaServerConnection"; }

    void connect();

    void onLinkEvent(reactor::LinkEvent);

    void onTimerEvent();

private:
    static constexpr long connectTimeout = 500000;
    static constexpr long receiveTimeout = 500000;
    static constexpr long establishTimeout = 500000;

    friend ServerConnectionInit;
    friend ServerConnectionConnecting;
    friend ServerConnectionReceiveHello;
    friend ServerConnectionEstablished;

    void connectLink();

    void closeLink();

    Result sendReverseHello();

    void receivePreaction();

    Result receiveHello();

    Result sendAcknowledge();

    void startTimer(long);

    void stopTimer();

    reactor::LinkPtr link;
    reactor::TimerPtr timer;
    OpcUaBinaryCodec codec;

};

} // namespace ua
