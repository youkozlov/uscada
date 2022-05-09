#include "OpcUaClientSecureChannelConnecting.hpp"
#include "OpcUaClientSecureChannelInit.hpp"
#include "OpcUaClientSecureChannelReceiveOpenRsp.hpp"
#include "OpcUaClientSecureChannel.hpp"

namespace app::ua
{

void OpcUaClientSecureChannelConnecting::onConnected(OpcUaClientSecureChannel& fsm)
{
    switch (fsm.sendOpenSecureChannelReq())
    {
    case OpcUaSecureChannel::Result::noerror:
    {
        LM(UA, LE, "Unexpected");
        fsm.notifyError();
    }
    break;
    case OpcUaSecureChannel::Result::done:
    {
        fsm.transit<OpcUaClientSecureChannelReceiveOpenRsp>();
    }
    break;
    case OpcUaSecureChannel::Result::error:
    {
        fsm.notifyError();
    }
    break;
    }
}

void OpcUaClientSecureChannelConnecting::onClosed(OpcUaClientSecureChannel& fsm)
{
    fsm.notifyClosed();
    fsm.transit<OpcUaClientSecureChannelInit>();
}

void OpcUaClientSecureChannelConnecting::onError(OpcUaClientSecureChannel& fsm)
{
    fsm.notifyError();
    fsm.transit<OpcUaClientSecureChannelInit>();
}

} // namespace app::ua
