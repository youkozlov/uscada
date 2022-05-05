#include "OpcUaServerSecureChannel.hpp"
#include "OpcUaServerSecureChannelInit.hpp"
#include "OpcUaSecureChannelCodec.hpp"
#include "OpcUaProtocolDefs.hpp"

namespace app::ua
{

OpcUaServerSecureChannel::OpcUaServerSecureChannel()
    : FsmBase(&app::getSingleton<OpcUaServerSecureChannelInit>())
{
}

OpcUaServerSecureChannel::~OpcUaServerSecureChannel()
{
}

void OpcUaServerSecureChannel::onConnected(OpcUaConnection&)
{
    getState().onConnected(*this);
}

void OpcUaServerSecureChannel::onDataReceived(OpcUaConnection& connection)
{
    getState().onDataReceived(*this, connection);
}

void OpcUaServerSecureChannel::onError()
{
    getState().onError(*this);
}

void OpcUaServerSecureChannel::onClosed()
{
    getState().onClosed(*this);
}

OpcUaSecureChannel::Result OpcUaServerSecureChannel::receiveOpenSecureChannelReq(OpcUaConnection& connection)
{
    if (not isOpnMsg(connection.getRxBuffer().begin()))
    {
        LM(UA, LE, "OpcUaServerSecureChannel-0, unexpected packet type");
        return Result::error;
    }

    OpcUaBinaryCodec codec(connection.getRxBuffer());
    UascMessageHeader hdr;
    codec >> hdr;

    UascSecurityHeader secHdr;
    codec >> secHdr;

    UascSequenceHeader seqHdr;
    codec >> seqHdr;

    UascOpenSecureChannelReq req;
    codec >> req;

    return OpcUaSecureChannel::Result::done;
}

OpcUaSecureChannel::Result OpcUaServerSecureChannel::sendOpenSecureChannelRsp(OpcUaConnection& connection)
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

    UascOpenSecureChannelRsp rsp;
    rsp.serverProtocolVer = opcUaProtocolVersion;
    codec << rsp;

    setPayloadSizeToHdr(tx.begin(), tx.size());
    LM(UA, LD, "OpcUaServerSecureChannel-0, send UascOpenSecureChannelRsp, pkt size(%u)", tx.size());

    connection.send(tx);
    return OpcUaSecureChannel::Result::done;
}

} // namespace app::ua
