#include "OpcUaServerSecureChannelReceiveOpenReq.hpp"
#include "OpcUaServerSecureChannelInit.hpp"
#include "OpcUaServerSecureChannelEstablished.hpp"
#include "OpcUaServerSecureChannel.hpp"

namespace app::ua
{

void OpcUaServerSecureChannelReceiveOpenReq::onDataReceived(OpcUaServerSecureChannel& fsm, OpcUaConnection& connection)
{
    switch (fsm.receiveOpenSecureChannelReq(connection))
    {
    case OpcUaSecureChannel::Result::noerror:
    break;
    case OpcUaSecureChannel::Result::done:
    {
        switch (fsm.sendOpenSecureChannelRsp(connection))
        {
        case OpcUaSecureChannel::Result::noerror:
        {
            LM(UA, LE, "Unexpected");
        }
        break;
        case OpcUaSecureChannel::Result::done:
        {
            fsm.transit<OpcUaServerSecureChannelEstablished>();
        }
        break;
        case OpcUaSecureChannel::Result::error:
        {
            fsm.notifyError();
            fsm.transit<OpcUaServerSecureChannelInit>();
        }
        break;
        }
    }
    break;
    case OpcUaSecureChannel::Result::error:
    {
        fsm.notifyError();
        fsm.transit<OpcUaServerSecureChannelInit>();
    }
    break;
    }
}

void OpcUaServerSecureChannelReceiveOpenReq::onClosed(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyClosed();
}

void OpcUaServerSecureChannelReceiveOpenReq::onError(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyError();
}

} // namespace app::ua
