#include "OpcUaServer.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaGetEndpoints.hpp"
#include "UaCreateSession.hpp"
#include "UaCloseSession.hpp"
#include "UaActivateSession.hpp"
#include "UaRead.hpp"

namespace app::ua
{

OpcUaServer::OpcUaServer(reactor::ReactorInterface& reactor_)
    : reactor(reactor_)
    , channelPool("channel", reactor)
    , sessionController(reactor)
{
    services[DataTypeId::GetEndpointsRequest_Encoding_DefaultBinary] = std::make_unique<UaGetEndpoints>();
    services[DataTypeId::CreateSessionRequest_Encoding_DefaultBinary] = std::make_unique<UaCreateSession>(sessionController);
    services[DataTypeId::CloseSessionRequest_Encoding_DefaultBinary] = std::make_unique<UaCloseSession>(sessionController);
    services[DataTypeId::ActivateSessionRequest_Encoding_DefaultBinary] = std::make_unique<UaActivateSession>(sessionController);
    services[DataTypeId::ReadRequest_Encoding_DefaultBinary] = std::make_unique<UaRead>(attributeController);

}

OpcUaServer::~OpcUaServer()
{
}

void OpcUaServer::listen(reactor::LinkAddr& addr)
{
    acceptor = reactor.createAcceptor([this](){ onAcceptEvent(); });
    acceptor->listen(addr);
}

void OpcUaServer::onAcceptEvent()
{
    LM(UA, LD, "onAcceptEvent");

    auto link = reactor.createLink({});
    acceptor->accept(*link);

    unsigned uid;
    if (not channelPool.alloc(uid))
    {
        LM(UA, LE, "Can not alloc channel");
        return;
    }
    auto& channel = channelPool.get(uid);
    channel.setHandler([this](auto const& ev){ onSecureChannelEvent(ev); });
    channel.open(link);
}

void OpcUaServer::onSecureChannelReq(OpcUaSecureChannel& channel)
{
    LM(UA, LD, "onSecureChannelEvent, request");

    OpcUaBinaryCodec codec(channel.getRxBuffer());

    ExpandedNodeId eNodeId;
    codec >> eNodeId;

    if (std::holds_alternative<UInt32>(eNodeId.nodeId.value))
    {
        std::uint32_t nodeId = std::get<UInt32>(eNodeId.nodeId.value);
        auto& serv = services[static_cast<DataTypeId>(nodeId)];
        if (not serv)
        {
            LM(UA, LE, "Unexpected nodeId(%u) service", nodeId);
            return;
        }
        serv->process(channel);
    }
    else
    {
        LM(UA, LE, "Unexpected nodeId format");
    }
}

void OpcUaServer::onSecureChannelRelease(OpcUaSecureChannel& channel)
{
    channel.setHandler({});
    channelPool.release(channel.getUid());
}

void OpcUaServer::onSecureChannelEvent(OpcUaSecureChannelEvent const& ev)
{
    switch (ev.type)
    {
    case OpcUaSecureChannelEvent::established:
        LM(UA, LD, "onSecureChannelEvent, established");
    break;
    case OpcUaSecureChannelEvent::request:
        onSecureChannelReq(ev.channel);
    break;
    case OpcUaSecureChannelEvent::closed:
    case OpcUaSecureChannelEvent::error:
        onSecureChannelRelease(ev.channel);
    break;
    }
}

} // namespace app::ua
