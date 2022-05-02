#pragma once

#include "FsmBase.hpp"
#include "ReactorInterface.hpp"
#include "ClientConnectionState.hpp"
#include "LinkPtr.hpp"
#include "TimerPtr.hpp"
#include "ConnectionProtocolCodec.hpp"

namespace app::ua
{

class ClientConnectionInit;
class ClientConnectionConnecting;
class ClientConnectionReceiveAck;
class ClientConnectionEstablished;

class ClientConnection : public app::FsmBase<ClientConnection, ClientConnectionState>
{
public:
    enum class Result
    {
          noerror
        , done
        , error
    };

    ClientConnection(reactor::ReactorInterface&);

    ~ClientConnection();

    char const* name() const { return "OpcUaServerConnection"; }

    void connect();

    void onLinkEvent(reactor::LinkEvent);

    void onTimerEvent();

private:
    static constexpr long connectTimeout = 500000;
    static constexpr long receiveTimeout = 500000;
    static constexpr long establishTimeout = 500000;

    friend ClientConnectionInit;
    friend ClientConnectionConnecting;
    friend ClientConnectionReceiveAck;
    friend ClientConnectionEstablished;

    void connectLink();

    void closeLink();

    void receivePreaction();

    Result receiveAck();

    Result sendHello();

    void startTimer(long);

    void stopTimer();

    reactor::LinkPtr link;
    reactor::TimerPtr timer;
    OpcUaBinaryCodec codec;
};

} // namespace app::ua
