#include "OpcUaClientSecureChannelInit.hpp"
#include "OpcUaClientSecureChannelReceiveOpenRsp.hpp"
#include "OpcUaClientSecureChannel.hpp"

namespace app::ua
{

void OpcUaClientSecureChannelInit::onConnected(OpcUaClientSecureChannel& fsm, OpcUaConnection& connection)
{
    switch (fsm.sendOpenSecureChannelReq(connection))
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

void OpcUaClientSecureChannelInit::onClosed(OpcUaClientSecureChannel& fsm)
{
    fsm.notifyClosed();
}

void OpcUaClientSecureChannelInit::onError(OpcUaClientSecureChannel& fsm)
{
    fsm.notifyError();
}

} // namespace app::ua
