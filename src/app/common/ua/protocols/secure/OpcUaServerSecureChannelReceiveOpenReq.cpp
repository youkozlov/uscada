#include "OpcUaServerSecureChannelReceiveOpenReq.hpp"
#include "OpcUaServerSecureChannelInit.hpp"
#include "OpcUaServerSecureChannelEstablished.hpp"
#include "OpcUaServerSecureChannel.hpp"

namespace app::ua
{

void OpcUaServerSecureChannelReceiveOpenReq::onOpenSecureChannelReq(OpcUaServerSecureChannel& fsm)
{
    switch (fsm.receiveOpenSecureChannelReq())
    {
    case OpcUaSecureChannel::Result::noerror:
    break;
    case OpcUaSecureChannel::Result::done:
    {
        switch (fsm.sendOpenSecureChannelRsp())
        {
        case OpcUaSecureChannel::Result::done:
        {
            fsm.transit<OpcUaServerSecureChannelEstablished>();
        }
        break;
        case OpcUaSecureChannel::Result::noerror:
        case OpcUaSecureChannel::Result::error:
        {
            fsm.notifyError();
            fsm.closeConnection();
            fsm.transit<OpcUaServerSecureChannelInit>();
        }
        break;
        }
    }
    break;
    case OpcUaSecureChannel::Result::error:
    {
        fsm.notifyError();
        fsm.closeConnection();
        fsm.transit<OpcUaServerSecureChannelInit>();
    }
    break;
    }
}

void OpcUaServerSecureChannelReceiveOpenReq::onClosed(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyClosed();
    fsm.transit<OpcUaServerSecureChannelInit>();
}

void OpcUaServerSecureChannelReceiveOpenReq::onError(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyError();
    fsm.transit<OpcUaServerSecureChannelInit>();
}

} // namespace app::ua
