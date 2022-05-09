#include "OpcUaServerSecureChannel.hpp"
#include "OpcUaServerSecureChannelInit.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "OpcUaProtocolDefs.hpp"
#include "TimeUtils.hpp"

namespace app::ua
{

OpcUaServerSecureChannel::OpcUaServerSecureChannel(EntityId uid, reactor::ReactorInterface& reactor)
    : FsmBase(&app::getSingleton<OpcUaServerSecureChannelInit>(), "OpcUaServerSecureChannel")
    , OpcUaSecureChannel(uid)
    , connection(reactor, *this)
{
}

OpcUaServerSecureChannel::~OpcUaServerSecureChannel()
{
}

void OpcUaServerSecureChannel::onConnectionConnectedEvent()
{
    getState().onConnected(*this);
}

void OpcUaServerSecureChannel::onConnectionDataReceivedEvent()
{
    if (isOpnMsg(connection.getRxBuffer().begin()))
    {
        getState().onOpenSecureChannelReq(*this);
    }
    else if (isCloMsg(connection.getRxBuffer().begin()))
    {
        getState().onCloseSecureChannelReq(*this);
    }
    else if (isSecMsg(connection.getRxBuffer().begin()))
    {
        getState().onSecureChannelReq(*this);
    }
    else
    {
        LM(UA, LE, "OpcUaServerSecureChannel-0, unexpected packet type");
    }
}

void OpcUaServerSecureChannel::onConnectionErrorEvent()
{
    getState().onError(*this);
}

void OpcUaServerSecureChannel::onConnectionClosedEvent()
{
    getState().onClosed(*this);
}

void OpcUaServerSecureChannel::open(reactor::LinkPtr& link)
{
    getState().onOpen(*this, link);
}

void OpcUaServerSecureChannel::close()
{
    //getState().onClosed(*this);
}

OpcUaSduBuffer& OpcUaServerSecureChannel::getRxBuffer()
{
    return connection.getRxBuffer();
}

void OpcUaServerSecureChannel::acceptConnection(reactor::LinkPtr& link)
{
    secureChannelId = ::rand() % 0x7FFFFFFF;

    connection.accept(link);
}

void OpcUaServerSecureChannel::closeConnection()
{
    connection.close();
}

OpcUaSecureChannel::Result OpcUaServerSecureChannel::receiveOpenSecureChannelReq()
{
    OpcUaBinaryCodec codec(connection.getRxBuffer());

    UaMessageHeader hdr;
    codec >> hdr;

    UaSecurityHeader secHdr;
    codec >> secHdr;

    UaSequenceHeader seqHdr;
    codec >> seqHdr;

    storedRxSequenceNumber = seqHdr.sequenceNumber;
    storedRequestId = seqHdr.requestId;

    UaOpenSecureChannelReqCont req;
    codec >> req;

    storedRequestedLifetime = req.msg.requestLifetime;

    return Result::done;
}

OpcUaSecureChannel::Result OpcUaServerSecureChannel::receiveCloseSecureChannelReq()
{
    OpcUaBinaryCodec codec(connection.getRxBuffer());

    UaMessageHeader hdr;
    codec >> hdr;

    UaSecurityTokenHeader secHdr;
    codec >> secHdr;

    if (secHdr.tokenId != tokenId)
    {
        LM(UA, LE, "OpcUaServerSecureChannel-0, unexpected tokenId");
        return Result::error;
    }

    UaSequenceHeader seqHdr;
    codec >> seqHdr;

    if (seqHdr.sequenceNumber != (storedRxSequenceNumber + 1))
    {
        LM(UA, LE, "OpcUaServerSecureChannel-0, unexpected sequenceNumber");
        return Result::error;
    }

    return OpcUaSecureChannel::Result::done;
}

OpcUaSecureChannel::Result OpcUaServerSecureChannel::receiveSecureChannelReq()
{
    OpcUaBinaryCodec codec(connection.getRxBuffer());

    UaMessageHeader hdr;
    codec >> hdr;

    UaSecurityTokenHeader secHdr;
    codec >> secHdr;

    if (secHdr.tokenId != tokenId)
    {
        LM(UA, LE, "OpcUaServerSecureChannel-0, unexpected tokenId");
        return Result::error;
    }

    UaSequenceHeader seqHdr;
    codec >> seqHdr;

    if (seqHdr.sequenceNumber != (storedRxSequenceNumber + 1))
    {
        LM(UA, LE, "OpcUaServerSecureChannel-0, unexpected sequenceNumber");
        return Result::error;
    }
    storedRxSequenceNumber = seqHdr.sequenceNumber;
    storedRequestId = seqHdr.requestId;

    return OpcUaSecureChannel::Result::done;
}

void OpcUaServerSecureChannel::send(OpcUaSduBuffer const& buf)
{
    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);

    UaMessageHeader hdr;
    hdr.messageType[0] = 'M';
    hdr.messageType[1] = 'S';
    hdr.messageType[2] = 'G';
    hdr.isFinal = 'F';
    hdr.secureChannelId = secureChannelId;
    codec << hdr;

    UaSecurityTokenHeader secHdr;
    secHdr.tokenId = tokenId;
    codec << secHdr;

    UaSequenceHeader seqHdr;
    seqHdr.sequenceNumber = sequenceNumberTx++;
    seqHdr.requestId = storedRequestId;
    codec << seqHdr;

    std::memcpy(tx.end(), buf.begin(), buf.size());
    tx.seek(buf.size());

    setPayloadSizeToHdr(tx.begin(), tx.size());

    switch (connection.send(tx))
    {
    case OpcUaConnection::Result::done:
    break;
    case OpcUaConnection::Result::noerror:
    case OpcUaConnection::Result::error:
    {}
    break;
    }
}

OpcUaSecureChannel::Result OpcUaServerSecureChannel::sendOpenSecureChannelRsp()
{
    tokenId = ::rand() % 0x7FFFFFFF;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);

    UaMessageHeader hdr;
    hdr.messageType[0] = 'O';
    hdr.messageType[1] = 'P';
    hdr.messageType[2] = 'N';
    hdr.isFinal = 'F';
    hdr.secureChannelId = secureChannelId;
    codec << hdr;

    UaSecurityHeader secHdr;
    secHdr.securityPolicyUri = "http://opcfoundation.org/UA/SecurityPolicy#None";
    codec << secHdr;

    UaSequenceHeader seqHdr;
    seqHdr.sequenceNumber = sequenceNumberTx++;
    seqHdr.requestId = storedRequestId;
    codec << seqHdr;

    UaOpenSecureChannelRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.serverProtocolVer = opcUaProtocolVersion;
    rsp.msg.securityToken.secureChannelId = secureChannelId;
    rsp.msg.securityToken.tokenId = tokenId;
    rsp.msg.securityToken.createdAt = utils::getCurrentDateTime();
    rsp.msg.securityToken.revisedLifetime = storedRequestedLifetime;
    codec << rsp;

    setPayloadSizeToHdr(tx.begin(), tx.size());
    LM(UA, LD, "OpcUaServerSecureChannel-0, send UaOpenSecureChannelRsp, pkt size(%u)", tx.size());

    switch (connection.send(tx))
    {
    case OpcUaConnection::Result::done:
    break;
    case OpcUaConnection::Result::noerror:
    case OpcUaConnection::Result::error:
    {
        return OpcUaSecureChannel::Result::error;
    }
    break;
    }
    return OpcUaSecureChannel::Result::done;
}

} // namespace app::ua
