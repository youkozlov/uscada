#include "UaServerSecureChannel.hpp"
#include "UaServerSecureChannelInit.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "OpcUaProtocolDefs.hpp"
#include "TimeUtils.hpp"
#include "UaSecureChannelSender.hpp"

namespace app::ua::securechannel
{

UaServerSecureChannel::UaServerSecureChannel(EntityId uid_, reactor::ReactorInterface& reactor_, ReleaserInterface& releaser_)
    : FsmBase(&app::getSingleton<UaServerSecureChannelInit>(), "UaServerSecureChannel")
    , secureChannelId(uid_)
    , reactor(reactor_)
    , releaser(releaser_)
{
}

UaServerSecureChannel::~UaServerSecureChannel()
{
}

void UaServerSecureChannel::release()
{
    sequenceNumberTx = 0;
    connectionId = {};
    sessionId = {};
    releaser.release(secureChannelId);
}

void UaServerSecureChannel::sendUaConnectionReleaseReq(UaConnectionId connectionId)
{
    reactor::MsgStore<MsgUaConnectionReleaseReq> msgStore;
    auto& msg = msgStore.getMsg();
    msg.connectionId = connectionId;
    Sender::sendMsg(msgStore);
}

UaServerSecureChannel::Result UaServerSecureChannel::receive(MsgUaOpenSecureChannelReq const& msgReq)
{
    OpcUaSduBuffer rx;
    std::memcpy(rx.end(), &msgReq.data[0], msgReq.length);
    rx.seek(msgReq.length);

    OpcUaBinaryCodec rxCodec(rx);

    UaSecurityHeader rxSecHdr;
    rxCodec >> rxSecHdr;
    UaSequenceHeader rxSeqHdr;
    rxCodec >> rxSeqHdr;
    UaOpenSecureChannelReqCont req;
    rxCodec >> req;

    connectionId = msgReq.connectionId;
    storedRxSequenceNumber = rxSeqHdr.sequenceNumber;
    storedTokenId = ::rand() % 0x7FFFFFFF;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec txCodec(tx);

    UaSecurityHeader txSecHdr;
    txSecHdr.securityPolicyUri = "http://opcfoundation.org/UA/SecurityPolicy#None";
    txCodec << txSecHdr;

    UaSequenceHeader txSeqHdr;
    txSeqHdr.sequenceNumber = sequenceNumberTx++;
    txSeqHdr.requestId = rxSeqHdr.requestId;
    txCodec << txSeqHdr;

    UaOpenSecureChannelRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.msg.requestHdr.requestHandle;
    rsp.msg.serverProtocolVer = opcUaProtocolVersion;
    rsp.msg.securityToken.secureChannelId = secureChannelId;
    rsp.msg.securityToken.tokenId = storedTokenId;
    rsp.msg.securityToken.createdAt = utils::getCurrentDateTime();
    rsp.msg.securityToken.revisedLifetime = req.msg.requestLifetime;
    txCodec << rsp;

    reactor::MsgStore<MsgUaOpenSecureChannelRsp> msgStore;
    auto& msgRsp = msgStore.getMsg();
    msgRsp.connectionId = msgReq.connectionId;
    msgRsp.secureChannelId = secureChannelId;
    msgRsp.chunkType = UaChunkType::fromUint8('F');
    msgRsp.length = tx.size();
    std::memcpy(&msgRsp.data[0], tx.begin(), tx.size());
    Sender::sendMsg(msgStore);

    return Result::done;
}

UaServerSecureChannel::Result UaServerSecureChannel::receive(MsgUaCloseSecureChannelReq const& msgReq)
{
    if (not connectionId || *connectionId != msgReq.connectionId)
    {
        LM(UASC, LE, "Uid-%u, unexpected connectionId", secureChannelId);
        return Result::error;
    }

    OpcUaSduBuffer rx;
    std::memcpy(rx.end(), &msgReq.data[0], msgReq.length);
    rx.seek(msgReq.length);

    OpcUaBinaryCodec rxCodec(rx);

    UaSecurityTokenHeader rxSecHdr;
    rxCodec >> rxSecHdr;

    if (rxSecHdr.tokenId != storedTokenId)
    {
        LM(UASC, LE, "Uid-%u, unexpected tokenId", secureChannelId);
        return Result::error;
    }

    UaSequenceHeader rxSeqHdr;
    rxCodec >> rxSeqHdr;

    if (rxSeqHdr.sequenceNumber != (storedRxSequenceNumber + 1))
    {
        LM(UASC, LE, "Uid-%u, unexpected sequenceNumber", secureChannelId);
        return Result::error;
    }
    storedRxSequenceNumber = rxSeqHdr.sequenceNumber;

    UaCloseSecureChannelReqCont req;
    rxCodec >> req;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec txCodec(tx);

    UaSecurityTokenHeader txSecHdr;
    txSecHdr.tokenId = storedTokenId;
    txCodec << txSecHdr;

    UaSequenceHeader txSeqHdr;
    txSeqHdr.sequenceNumber = sequenceNumberTx++;
    txSeqHdr.requestId = rxSeqHdr.requestId;
    txCodec << txSeqHdr;

    UaCloseSecureChannelRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.msg.requestHdr.requestHandle;
    txCodec << rsp;

    reactor::MsgStore<MsgUaCloseSecureChannelRsp> msgStore;
    auto& msgRsp = msgStore.getMsg();
    msgRsp.connectionId = msgReq.connectionId;
    msgRsp.secureChannelId = secureChannelId;
    msgRsp.chunkType = UaChunkType::fromUint8('F');
    msgRsp.length = tx.size();
    std::memcpy(&msgRsp.data[0], tx.begin(), tx.size());
    Sender::sendMsg(msgStore);

    return Result::done;
}

UaServerSecureChannel::Result UaServerSecureChannel::receive(MsgUaAssociateSecureChannelReq const& msgReq)
{
    if (not connectionId || *connectionId != msgReq.hdr.connectionId)
    {
        LM(UASC, LE, "Uid-%u, unexpected connectionId", secureChannelId);
        return Result::error;
    }

    sessionId = msgReq.hdr.sessionId;
    return Result::done;
}

UaServerSecureChannel::Result UaServerSecureChannel::receive(MsgUaSecuredMessageReceiveInd const& msgReq)
{
    if (not connectionId || *connectionId != msgReq.connectionId)
    {
        LM(UASC, LE, "Uid-%u, unexpected connectionId", secureChannelId);
        return Result::error;
    }

    OpcUaSduBuffer rx;
    std::memcpy(rx.end(), &msgReq.data[0], msgReq.length);
    rx.seek(msgReq.length);

    OpcUaBinaryCodec rxCodec(rx);

    UaSecurityTokenHeader rxSecHdr;
    rxCodec >> rxSecHdr;

    if (rxSecHdr.tokenId != storedTokenId)
    {
        LM(UASC, LE, "Uid-%u, unexpected tokenId", secureChannelId);
        return Result::error;
    }

    UaSequenceHeader rxSeqHdr;
    rxCodec >> rxSeqHdr;

    if (rxSeqHdr.sequenceNumber != (storedRxSequenceNumber + 1))
    {
        LM(UASC, LE, "Uid-%u, unexpected sequenceNumber", secureChannelId);
        return Result::error;
    }
    storedRxSequenceNumber = rxSeqHdr.sequenceNumber;

    reactor::MsgStore<MsgUaEncodedMessageReceiveInd> msgStore;
    auto& msgRsp = msgStore.getMsg();
    msgRsp.hdr.connectionId = msgReq.connectionId;
    msgRsp.hdr.secureChannelId = secureChannelId;
    msgRsp.hdr.requestId = rxSeqHdr.requestId;
    msgRsp.hdr.sessionId = sessionId ? *sessionId : invalidSuid;
    msgRsp.length = rx.size();
    std::memcpy(&msgRsp.data[0], rx.begin(), rx.size());
    Sender::sendMsg(msgStore);

    return Result::done;
}

UaServerSecureChannel::Result UaServerSecureChannel::receive(MsgUaEncodedMessageSendReq const& msgReq)
{
    if (not connectionId || *connectionId != msgReq.hdr.connectionId)
    {
        LM(UASC, LE, "Uid-%u, unexpected connectionId", secureChannelId);
        return Result::error;
    }
    if (sessionId && *sessionId != msgReq.hdr.sessionId)
    {
        LM(UASC, LE, "Uid-%u, unexpected sessionId", secureChannelId);
        return Result::error;
    }

    OpcUaSduBuffer tx;

    OpcUaBinaryCodec codec(tx);

    UaSecurityTokenHeader secHdr;
    secHdr.tokenId = storedTokenId;
    codec << secHdr;

    UaSequenceHeader seqHdr;
    seqHdr.requestId = msgReq.hdr.requestId;
    seqHdr.sequenceNumber = sequenceNumberTx++;
    codec << seqHdr;

    std::memcpy(tx.end(), &msgReq.data[0], msgReq.length);
    tx.seek(msgReq.length);

    reactor::MsgStore<MsgUaSecuredMessageSendReq> msgStore;
    auto& msgRsp = msgStore.getMsg();
    msgRsp.connectionId = msgReq.hdr.connectionId;
    msgRsp.secureChannelId = secureChannelId;
    msgRsp.chunkType = UaChunkType::fromUint8('F');
    msgRsp.length = tx.size();
    std::memcpy(&msgRsp.data[0], tx.begin(), tx.size());
    Sender::sendMsg(msgStore);

    return Result::done;
}



} // namespace app::ua::securechannel
