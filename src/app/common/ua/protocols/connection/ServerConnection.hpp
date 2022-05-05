#pragma once

#include "FsmBase.hpp"
#include "ReactorInterface.hpp"
#include "ServerConnectionState.hpp"
#include "LinkPtr.hpp"
#include "LinkAddr.hpp"
#include "TimerPtr.hpp"
#include "OpcUaConnection.hpp"

namespace app::ua
{

class ServerConnectionInit;
class ServerConnectionConnecting;
class ServerConnectionReceiveHello;
class ServerConnectionConnected;

class ServerConnection : public app::FsmBase<ServerConnection, ServerConnectionState>
                       , public OpcUaConnection
{
public:
    explicit ServerConnection(reactor::ReactorInterface&);

    ~ServerConnection();

    char const* name() const { return "OpcUaServerConnection"; }

    void connect(reactor::LinkAddr const&);

    void accept(reactor::LinkPtr&);

    void onLinkEvent(reactor::LinkEvent) final;

    void onTimerEvent() final;

    void close();

private:
    static constexpr long connectTimeout = 3000000;
    static constexpr long receiveTimeout = 1000000;
    static constexpr long establishTimeout = 10000000;

    friend ServerConnectionInit;
    friend ServerConnectionConnecting;
    friend ServerConnectionReceiveHello;
    friend ServerConnectionConnected;

    Result sendReverseHello();

    Result receiveHello();

    Result receiveMessage();

    Result sendAcknowledge();
};

} // namespace app::ua
