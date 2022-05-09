#pragma once

#include "FsmBase.hpp"
#include "OpcUaServerSecureChannelState.hpp"
#include "OpcUaSecureChannel.hpp"
#include "ServerConnection.hpp"

namespace app::ua
{

class OpcUaServerSecureChannelInit;
class OpcUaServerSecureChannelConnecting;
class OpcUaServerSecureChannelReceiveOpenReq;
class OpcUaServerSecureChannelEstablished;

class OpcUaServerSecureChannel : public app::FsmBase<OpcUaServerSecureChannel, OpcUaServerSecureChannelState>
                               , public OpcUaSecureChannel
                               , public OpcUaConnectionHandler
{
public:
    using SecureChannelHandler = std::function<void()>;

    explicit OpcUaServerSecureChannel(EntityId, reactor::ReactorInterface&);

    ~OpcUaServerSecureChannel();

    void open(reactor::LinkPtr&);

    void close() final;

    OpcUaSduBuffer& getRxBuffer() final;

    void send(OpcUaSduBuffer const&) final;

private:
    friend OpcUaServerSecureChannelInit;
    friend OpcUaServerSecureChannelConnecting;
    friend OpcUaServerSecureChannelReceiveOpenReq;
    friend OpcUaServerSecureChannelEstablished;

    void onConnectionConnectedEvent() final;
    void onConnectionDataReceivedEvent() final;
    void onConnectionErrorEvent() final;
    void onConnectionClosedEvent() final;

    void acceptConnection(reactor::LinkPtr&);
    void closeConnection();
    Result receiveOpenSecureChannelReq();
    Result receiveCloseSecureChannelReq();
    Result receiveSecureChannelReq();
    Result sendOpenSecureChannelRsp();

    OpcUaSecureChannelHandler handler;
    ServerConnection          connection;

    std::uint32_t secureChannelId;
    std::uint32_t sequenceNumberTx{1};
    std::uint32_t storedRxSequenceNumber;
    std::uint32_t storedRequestId;
    std::uint32_t storedRequestedLifetime;
    std::uint32_t tokenId;
};

} // namespace app::ua
