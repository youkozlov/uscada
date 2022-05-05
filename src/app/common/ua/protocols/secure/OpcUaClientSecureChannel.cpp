#include "OpcUaClientSecureChannel.hpp"
#include "OpcUaClientSecureChannelInit.hpp"
#include "OpcUaSecureChannelCodec.hpp"
#include "OpcUaProtocolDefs.hpp"

namespace app::ua
{

OpcUaClientSecureChannel::OpcUaClientSecureChannel()
    : FsmBase(&app::getSingleton<OpcUaClientSecureChannelInit>())
{
}

OpcUaClientSecureChannel::~OpcUaClientSecureChannel()
{
}

void OpcUaClientSecureChannel::onConnected(OpcUaConnection& connection)
{
    getState().onConnected(*this, connection);
}

void OpcUaClientSecureChannel::onDataReceived(OpcUaConnection& connection)
{
    getState().onDataReceived(*this, connection);
}

void OpcUaClientSecureChannel::onError()
{
    getState().onError(*this);
}

void OpcUaClientSecureChannel::onClosed()
{
    getState().onClosed(*this);
}

OpcUaSecureChannel::Result OpcUaClientSecureChannel::sendOpenSecureChannelReq(OpcUaConnection& connection)
{
    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    UascMessageHeader hdr;
    hdr.messageType[0] = 'O';
    hdr.messageType[1] = 'P';
    hdr.messageType[2] = 'N';
    hdr.isFinal = 'F';
    hdr.secureChannelId = 0;
    codec << hdr;

    UascSecurityHeader secHdr;
    codec << secHdr;

    UascSequenceHeader seqHdr;
    codec << seqHdr;

    UascOpenSecureChannelReq req;
    req.clientProtocolVer = opcUaProtocolVersion;
    codec << req;

    setPayloadSizeToHdr(tx.begin(), tx.size());
    LM(UA, LD, "OpcUaClientSecureChannel-0, send UascOpenSecureChannelReq, pkt size(%u)", tx.size());

    connection.send(tx);
    return OpcUaSecureChannel::Result::done;
}

OpcUaSecureChannel::Result OpcUaClientSecureChannel::receiveOpenSecureChannelRsp(OpcUaConnection& connection)
{
    if (not isOpnMsg(connection.getRxBuffer().begin()))
    {
        LM(UA, LE, "OpcUaClientSecureChannel-0, unexpected packet type");
        return Result::error;
    }

    OpcUaBinaryCodec codec(connection.getRxBuffer());
    UascMessageHeader hdr;
    codec >> hdr;

    UascSecurityHeader secHdr;
    codec >> secHdr;

    UascSequenceHeader seqHdr;
    codec >> seqHdr;

    UascOpenSecureChannelRsp rsp;
    codec >> rsp;

    return OpcUaSecureChannel::Result::done;
}

} // namespace app::ua
