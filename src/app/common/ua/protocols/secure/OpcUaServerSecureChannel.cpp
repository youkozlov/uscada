#include "OpcUaServerSecureChannel.hpp"

namespace app::ua
{

OpcUaServerSecureChannel::OpcUaServerSecureChannel()
    : FsmBase(&app::getSingleton<OpcUaServerSecureChannelStateInit>())
{
}

OpcUaServerSecureChannel::~OpcUaServerSecureChannel()
{
}

void OpcUaServerSecureChannel::processData(ServerConnection& connection)
{
    getState().onProcessData(*this, connection);
}

void OpcUaServerSecureChannel::receiveOpenSecureChannelReq(ServerConnection& connection)
{
}

void OpcUaServerSecureChannel::sendOpenSecureChannelRsp(ServerConnection& connection)
{
}

} // namespace app::ua
