#include "OpcUaClientSecureChannelReceiveOpenRsp.hpp"
#include "OpcUaClientSecureChannelInit.hpp"
#include "OpcUaClientSecureChannelEstablished.hpp"
#include "OpcUaClientSecureChannel.hpp"

namespace app::ua
{

void OpcUaClientSecureChannelReceiveOpenRsp::onDataReceived(OpcUaClientSecureChannel& fsm, OpcUaConnection& connection)
{
    switch (fsm.receiveOpenSecureChannelRsp(connection))
    {
    case OpcUaSecureChannel::Result::noerror:
    break;
    case OpcUaSecureChannel::Result::done:
    {
        fsm.transit<OpcUaClientSecureChannelEstablished>();
    }
    break;
    case OpcUaSecureChannel::Result::error:
    {
        fsm.notifyError();
        fsm.transit<OpcUaClientSecureChannelInit>();
    }
    break;
    }
}

void OpcUaClientSecureChannelReceiveOpenRsp::onClosed(OpcUaClientSecureChannel& fsm)
{
    fsm.notifyClosed();
}

void OpcUaClientSecureChannelReceiveOpenRsp::onError(OpcUaClientSecureChannel& fsm)
{
    fsm.notifyError();
}

} // namespace app::ua
