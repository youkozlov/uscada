#include "UaTransport.hpp"
#include "UaTransportReactor.hpp"

namespace app::ua::transport
{

UaTransport::UaTransport()
    : server(0u, Reactor::get())
{
}

UaTransport::~UaTransport()
{
}

void UaTransport::receive(MsgUaTransportConfigReq const& msg)
{
    server.listen(msg.addr);
}

void UaTransport::receive(MsgUaOpenSecureChannelRsp const& msg)
{
    server.receive(msg);
}

void UaTransport::receive(MsgUaCloseSecureChannelRsp const& msg)
{
    server.receive(msg);
}

void UaTransport::receive(MsgUaSecuredMessageSendReq const& msg)
{
    server.receive(msg);
}

void UaTransport::receive(MsgUaConnectionReleaseReq const& msg)
{
    server.receive(msg);
}

} // namespace app::ua::transport
