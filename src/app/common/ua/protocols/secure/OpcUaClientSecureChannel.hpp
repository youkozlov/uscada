#pragma once

#include "FsmBase.hpp"
#include "OpcUaClientSecureChannelState.hpp"
#include "OpcUaSecureChannel.hpp"
#include "ClientConnection.hpp"

namespace app::ua
{

class OpcUaClientSecureChannelInit;
class OpcUaClientSecureChannelConnecting;
class OpcUaClientSecureChannelReceiveOpenRsp;
class OpcUaClientSecureChannelEstablished;

class OpcUaClientSecureChannel : public app::FsmBase<OpcUaClientSecureChannel, OpcUaClientSecureChannelState>
                               , public OpcUaSecureChannel
                               , public OpcUaConnectionHandler
{
public:
    using SecureChannelHandler = std::function<void()>;

    OpcUaClientSecureChannel(EntityId, reactor::ReactorInterface&);

    ~OpcUaClientSecureChannel();

    void open(reactor::LinkAddr& addr);

    void close() final;

    OpcUaSduBuffer& getRxBuffer() final;

    void send(OpcUaSduBuffer const&) final;

private:
    friend OpcUaClientSecureChannelInit;
    friend OpcUaClientSecureChannelConnecting;
    friend OpcUaClientSecureChannelReceiveOpenRsp;
    friend OpcUaClientSecureChannelEstablished;

    void onConnectionConnectedEvent() final;
    void onConnectionDataReceivedEvent() final;
    void onConnectionErrorEvent() final;
    void onConnectionClosedEvent() final;

    void connectLink(reactor::LinkAddr&);
    Result sendOpenSecureChannelReq();
    Result receiveOpenSecureChannelRsp();

    OpcUaSecureChannelHandler handler;
    ClientConnection          connection;
};

} // namespace app::ua
