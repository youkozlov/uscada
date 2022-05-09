#include "OpcUaClientSecureChannel.hpp"
#include "OpcUaClientSecureChannelInit.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "OpcUaProtocolDefs.hpp"

namespace app::ua
{

OpcUaClientSecureChannel::OpcUaClientSecureChannel(EntityId uid, reactor::ReactorInterface& reactor_)
    : FsmBase(&app::getSingleton<OpcUaClientSecureChannelInit>(), "OpcUaClientSecureChannel")
    , OpcUaSecureChannel(uid)
    , connection(reactor_, *this)
{
}

OpcUaClientSecureChannel::~OpcUaClientSecureChannel()
{
}

void OpcUaClientSecureChannel::onConnectionConnectedEvent()
{
    getState().onConnected(*this);
}

void OpcUaClientSecureChannel::onConnectionDataReceivedEvent()
{
    getState().onDataReceived(*this);
}

void OpcUaClientSecureChannel::onConnectionErrorEvent()
{
    getState().onError(*this);
}

void OpcUaClientSecureChannel::onConnectionClosedEvent()
{
    getState().onClosed(*this);
}

void OpcUaClientSecureChannel::open(reactor::LinkAddr& addr)
{
    getState().onOpen(*this, addr);
}

void OpcUaClientSecureChannel::close()
{
}

OpcUaSduBuffer& OpcUaClientSecureChannel::getRxBuffer()
{
    return connection.getRxBuffer();
}

void OpcUaClientSecureChannel::send(OpcUaSduBuffer const&)
{
}

void OpcUaClientSecureChannel::connectLink(reactor::LinkAddr& addr)
{
    connection.connect(addr);
}

OpcUaSecureChannel::Result OpcUaClientSecureChannel::sendOpenSecureChannelReq()
{
    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);

    UaMessageHeader hdr;
    hdr.messageType[0] = 'O';
    hdr.messageType[1] = 'P';
    hdr.messageType[2] = 'N';
    hdr.isFinal = 'F';
    hdr.secureChannelId = 0;
    codec << hdr;

    UaSecurityHeader secHdr;
    codec << secHdr;

    UaSequenceHeader seqHdr;
    codec << seqHdr;

    UaOpenSecureChannelReqCont req;
    req.msg.clientProtocolVer = opcUaProtocolVersion;
    codec << req;

    setPayloadSizeToHdr(tx.begin(), tx.size());
    LM(UA, LD, "OpcUaClientSecureChannel-0, send UaOpenSecureChannelReq, pkt size(%u)", tx.size());

    connection.send(tx);
    return OpcUaSecureChannel::Result::done;
}

OpcUaSecureChannel::Result OpcUaClientSecureChannel::receiveOpenSecureChannelRsp()
{
    if (not isOpnMsg(connection.getRxBuffer().begin()))
    {
        LM(UA, LE, "OpcUaClientSecureChannel-0, unexpected packet type");
        return Result::error;
    }

    OpcUaBinaryCodec codec(connection.getRxBuffer());
    UaMessageHeader hdr;
    codec >> hdr;

    UaSecurityHeader secHdr;
    codec >> secHdr;

    UaSequenceHeader seqHdr;
    codec >> seqHdr;

    UaOpenSecureChannelRsp rsp;
    codec >> rsp;

    return OpcUaSecureChannel::Result::done;
}

} // namespace app::ua
