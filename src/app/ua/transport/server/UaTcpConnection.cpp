#include "UaTcpConnection.hpp"
#include "UaMessageHeader.hpp"
#include "UaTcpConnectionInit.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaTcpDefs.hpp"
#include "UaTransportSender.hpp"

namespace app::ua::transport
{

UaTcpConnection::UaTcpConnection(EntityId uid_, reactor::ReactorInterface& r, ReleaserInterface& releaser_)
    : FsmBase(&app::getSingleton<UaTcpConnectionInit>(), "UaTcpConnection")
    , connectionId(uid_)
    , reactor(r)
    , releaser(releaser_)
{
}

UaTcpConnection::~UaTcpConnection()
{
}

void UaTcpConnection::sendUaConnectionReleaseInd()
{
    if (not associatedSecureChannelId)
    {
        LM(UATL, LE, "Uid-%u, Can not send UaConnectionReleaseInd, secure channel id is undefined", connectionId);
        return;
    }
    reactor::MsgStore<MsgUaConnectionReleaseInd> msgStore;
    msgStore.getMsg().connectionId = connectionId;
    msgStore.getMsg().secureChannelId = *associatedSecureChannelId;
    Sender::sendMsg(msgStore);
}

UaTcpConnection::Result UaTcpConnection::receive(MsgUaSecuredMessageSendReq const& msg)
{
    if (not associatedSecureChannelId || *associatedSecureChannelId != msg.secureChannelId)
    {
        LM(UATL, LE, "Uid-%u, unexpected secureChannelId", connectionId);
        return Result::error;
    }

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    UaMessageHeader hdr;
    hdr.messageType[0] = 'M';
    hdr.messageType[1] = 'S';
    hdr.messageType[2] = 'G';
    hdr.isFinal = msg.chunkType.toUint8();
    hdr.secureChannelId = msg.secureChannelId;
    codec << hdr;

    std::memcpy(tx.end(), &msg.data[0], msg.length);
    tx.seek(msg.length);

    setPayloadSizeToHdr(tx.begin(), tx.size());

    int rc = link->send(tx.begin(), tx.size());
    if (rc <= 0)
    {
        LM(UATL, LE, "Uid-%u, send return: %d", connectionId, rc);
        return Result::error;
    }
    return Result::done;
}

UaTcpConnection::Result UaTcpConnection::receive(MsgUaOpenSecureChannelRsp const& msg)
{
    associatedSecureChannelId = msg.secureChannelId;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    UaMessageHeader hdr;
    hdr.messageType[0] = 'O';
    hdr.messageType[1] = 'P';
    hdr.messageType[2] = 'N';
    hdr.isFinal = msg.chunkType.toUint8();
    hdr.secureChannelId = msg.secureChannelId;
    codec << hdr;

    std::memcpy(tx.end(), &msg.data[0], msg.length);
    tx.seek(msg.length);

    setPayloadSizeToHdr(tx.begin(), tx.size());

    int rc = link->send(tx.begin(), tx.size());
    if (rc <= 0)
    {
        LM(UATL, LE, "Uid-%u, send return: %d", connectionId, rc);
        return Result::error;
    }
    return Result::done;
}

UaTcpConnection::Result UaTcpConnection::receive(MsgUaCloseSecureChannelRsp const& msg)
{
    if (not associatedSecureChannelId || *associatedSecureChannelId != msg.secureChannelId)
    {
        LM(UATL, LE, "Uid-%u, unexpected secureChannelId", connectionId);
        return Result::error;
    }

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    UaMessageHeader hdr;
    hdr.messageType[0] = 'C';
    hdr.messageType[1] = 'L';
    hdr.messageType[2] = 'O';
    hdr.isFinal = msg.chunkType.toUint8();
    hdr.secureChannelId = msg.secureChannelId;
    codec << hdr;

    std::memcpy(tx.end(), &msg.data[0], msg.length);
    tx.seek(msg.length);

    setPayloadSizeToHdr(tx.begin(), tx.size());

    int rc = link->send(tx.begin(), tx.size());
    if (rc <= 0)
    {
        LM(UATL, LE, "Uid-%u, send return: %d", connectionId, rc);
        return Result::error;
    }
    return Result::done;
}

void UaTcpConnection::acceptLink(reactor::LinkPtr& link_)
{
    link = std::move(link_);
    link->setHandler([this](auto ev)
    {
        switch (ev)
        {
        case reactor::LinkEvent::connected:
            getState().onConnected(*this);
        break;
        case reactor::LinkEvent::data:
            getState().onDataReceived(*this);
        break;
        case reactor::LinkEvent::error:
            getState().onError(*this);
        break;
        }
    });
}

void UaTcpConnection::release()
{
    associatedSecureChannelId = {};
    link.reset();
    timer.reset();
    releaser.release(connectionId);
}

void UaTcpConnection::allocTimer()
{
    timer = reactor.createTimer([this](){ getState().onTimer(*this); });
}

void UaTcpConnection::startTimer(long timeout)
{
    timer->start(timeout);
}

void UaTcpConnection::stopTimer()
{
    timer->stop();
}

void UaTcpConnection::receivePreaction()
{
    rxBuffer.reset();
}

UaTcpConnection::Result UaTcpConnection::receive()
{
    // TODO REMOVE MN
    if (rxBuffer.size() > 1024)
    {
        LM(UATL, LE, "Uid-%u, received packet is invalid", connectionId);
        return Result::error;
    }

    auto const& result = link->receive(rxBuffer.end(), rxBuffer.capacity());
    switch (result.status)
    {
    case reactor::LinkResult::ok:
    break;
    case reactor::LinkResult::na:
        return Result::noerror;
    case reactor::LinkResult::closed:
    case reactor::LinkResult::error:
        return Result::error;
    }

    rxBuffer.seek(result.len);

    if (rxBuffer.size() < messageHeaderSize)
    {
        return Result::noerror;
    }

    if (rxBuffer.size() < getMsgSizeFromHdr(rxBuffer.begin()))
    {
        return Result::noerror;
    }

    if (rxBuffer.size() != getMsgSizeFromHdr(rxBuffer.begin()))
    {
        LM(UATL, LE, "Uid-%u, packet has invalid size", connectionId);
        return Result::error;
    }

    return Result::done;
}

UaTcpConnection::Result UaTcpConnection::receiveHello()
{
    switch (receive())
    {
    case UaTcpConnection::Result::noerror:
        return UaTcpConnection::Result::noerror;
    case UaTcpConnection::Result::done:
    break;
    case UaTcpConnection::Result::error:
        return UaTcpConnection::Result::error;
    }

/*
    if (UaSecMsgType::opn != fromString(rxBuffer.begin()))
    {
        LM(UATL, LE, "Uid-%u, unexpected packet type", connectionId);
        return Result::error;
    }
*/
    OpcUaBinaryCodec codec(rxBuffer);

    MessageHeader hdr;
    HelloMessage hello;
    codec >> hdr >> hello;

    LM(UATL, LD, "Uid-%u, received HelloMessage", connectionId);

    return sendAcknowledge();
}

UaTcpConnection::Result UaTcpConnection::sendAcknowledge()
{
    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);

    MessageHeader hdr;
    hdr.messageType[0] = 'A';
    hdr.messageType[1] = 'C';
    hdr.messageType[2] = 'K';
    hdr.isFinal = 'F';
    codec << hdr;

    AcknowledgeMessage ack;
    ack.protocolVersion = opcUaProtocolVersion;
    ack.sendBufferSize = opcUaSendBufferSize;
    ack.receiveBufferSize = opcUaReceiveBufferSize;
    ack.maxMessageSize = opcUaMaxChunkCount * opcUaReceiveBufferSize;
    ack.maxChunkCount = opcUaMaxChunkCount;
    codec << ack;

    setPayloadSizeToHdr(tx.begin(), tx.size());

    LM(UATL, LD, "Uid-%u, send AcknowledgeMessage", connectionId);

    int rc = link->send(tx.begin(), tx.size());
    if (rc <= 0)
    {
        LM(UATL, LI, "Uid-%u, send return: %d", connectionId, rc);
        return Result::error;
    }
    return Result::done;
}

UaTcpConnection::Result UaTcpConnection::receiveSecuredMessage()
{
    switch (receive())
    {
    case UaTcpConnection::Result::noerror:
        return UaTcpConnection::Result::noerror;
    case UaTcpConnection::Result::done:
    break;
    case UaTcpConnection::Result::error:
        return UaTcpConnection::Result::error;
    }
    auto msgType = fromString(rxBuffer.begin());

    OpcUaBinaryCodec codec(rxBuffer);
    UaMessageHeader hdr;
    codec >> hdr;

    LM(UATL, LD, "Uid-%u, receiveSecuredMessage: %s", connectionId, toString(msgType).c_str());

    switch (msgType)
    {
    case UaSecMsgType::msg:
    {
        if (not associatedSecureChannelId || *associatedSecureChannelId != hdr.secureChannelId)
        {
            LM(UATL, LE, "Uid-%u, unexpected secureChannelId", connectionId);
            return Result::error;
        }
        reactor::MsgStore<MsgUaSecuredMessageReceiveInd> msgStore;
        auto& msg = msgStore.getMsg();
        msg.connectionId = connectionId;
        msg.secureChannelId = hdr.secureChannelId;
        msg.chunkType = UaChunkType::fromUint8(hdr.isFinal);
        msg.length = rxBuffer.size();
        std::memcpy(msg.data, rxBuffer.begin(), rxBuffer.size());
        Sender::sendMsg(msgStore);
    }
    break;
    case UaSecMsgType::opn:
    {
        reactor::MsgStore<MsgUaOpenSecureChannelReq> msgStore;
        auto& msg = msgStore.getMsg();
        msg.connectionId = connectionId;
        msg.secureChannelId = hdr.secureChannelId;
        msg.chunkType = UaChunkType::fromUint8(hdr.isFinal);
        msg.length = rxBuffer.size();
        std::memcpy(msg.data, rxBuffer.begin(), rxBuffer.size());
        Sender::sendMsg(msgStore);
    }
    break;
    case UaSecMsgType::clo:
    {
        if (not associatedSecureChannelId || *associatedSecureChannelId != hdr.secureChannelId)
        {
            LM(UATL, LE, "Uid-%u, unexpected secureChannelId", connectionId);
            return Result::error;
        }
        reactor::MsgStore<MsgUaCloseSecureChannelReq> msgStore;
        auto& msg = msgStore.getMsg();
        msg.connectionId = connectionId;
        msg.secureChannelId = hdr.secureChannelId;
        msg.chunkType = UaChunkType::fromUint8(hdr.isFinal);
        msg.length = rxBuffer.size();
        std::memcpy(msg.data, rxBuffer.begin(), rxBuffer.size());
        Sender::sendMsg(msgStore);
    }
    break;
    default:
    {
        LM(UATL, LE, "Uid-%u, unexpected", connectionId);
        return UaTcpConnection::Result::error;
    }
    break;
    }
    return UaTcpConnection::Result::done;
}

} // namespace app::ua::transport
