#include "OpcUaServerSecureChannelEstablished.hpp"
#include "OpcUaServerSecureChannelInit.hpp"
#include "OpcUaServerSecureChannel.hpp"

namespace app::ua
{

void OpcUaServerSecureChannelEstablished::onOpenSecureChannelReq(OpcUaServerSecureChannel& fsm)
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

void OpcUaServerSecureChannelEstablished::onCloseSecureChannelReq(OpcUaServerSecureChannel& fsm)
{
    switch (fsm.receiveCloseSecureChannelReq())
    {
    case OpcUaSecureChannel::Result::noerror:
    break;
    case OpcUaSecureChannel::Result::done:
    {
        fsm.notifyClosed();
        fsm.closeConnection();
        fsm.transit<OpcUaServerSecureChannelInit>();
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

void OpcUaServerSecureChannelEstablished::onSecureChannelReq(OpcUaServerSecureChannel& fsm)
{
    switch (fsm.receiveSecureChannelReq())
    {
    case OpcUaSecureChannel::Result::noerror:
    break;
    case OpcUaSecureChannel::Result::done:
    {
        fsm.notifyDataReceived();
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

void OpcUaServerSecureChannelEstablished::onClosed(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyClosed();
    fsm.transit<OpcUaServerSecureChannelInit>();
}

void OpcUaServerSecureChannelEstablished::onError(OpcUaServerSecureChannel& fsm)
{
    fsm.notifyError();
    fsm.transit<OpcUaServerSecureChannelInit>();
}

} // namespace app::ua
