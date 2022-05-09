#pragma once

#include "FsmBase.hpp"
#include "ReactorInterface.hpp"
#include "ClientConnectionState.hpp"
#include "LinkPtr.hpp"
#include "LinkAddr.hpp"
#include "TimerPtr.hpp"
#include "OpcUaConnection.hpp"

namespace app::ua
{

class ClientConnectionInit;
class ClientConnectionConnecting;
class ClientConnectionReceiveAck;
class ClientConnectionConnected;

class ClientConnection : public app::FsmBase<ClientConnection, ClientConnectionState>
                       , public OpcUaConnection
{
public:
    ClientConnection(reactor::ReactorInterface&, OpcUaConnectionHandler&);

    ~ClientConnection();

    void connect(reactor::LinkAddr const&);

    void close();

    void onLinkEvent(reactor::LinkEvent) final;

    void onTimerEvent() final;

private:
    static constexpr long connectTimeout = 3000000;
    static constexpr long receiveTimeout = 1000000;
    static constexpr long establishTimeout = 10000000;

    friend ClientConnectionInit;
    friend ClientConnectionConnecting;
    friend ClientConnectionReceiveAck;
    friend ClientConnectionConnected;

    Result receiveAck();

    Result sendHello();
};

} // namespace app::ua
