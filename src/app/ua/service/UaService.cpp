#include "UaService.hpp"
#include "UaServiceReactor.hpp"
#include "UaServiceSender.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaServiceId.hpp"
#include "Logger.hpp"

namespace app::ua::service
{

UaService::UaService()
    : sessionSrv(Reactor::get())
{
    discoverySrv.subscribe(*this);
    sessionSrv.subscribe(*this);
    attributeSrv.subscribe(*this);
}

UaService::~UaService()
{
}

void UaService::subscribeService(DataTypeId id, UaServiceInterfacePtr&& serv)
{
    services[id] = std::move(serv);
}

void UaService::receive(MsgUaServiceConfigReq const&)
{
}

void UaService::receive(MsgUaEncodedMessageReceiveInd const& msgReq)
{
    LM(UASRV, LD, "UaEncodedMessageReceiveInd, received");

    OpcUaSduBuffer rx;
    std::memcpy(rx.end(), &msgReq.data[0], msgReq.length);
    rx.seek(msgReq.length);

    OpcUaBinaryCodec codec(rx);
    ExpandedNodeId eNodeId;
    codec >> eNodeId;

    if (not std::holds_alternative<UInt32>(eNodeId.nodeId.value))
    {
        LM(UASC, LE, "Unexpected eNodeId format");
        return;
    }

    UaServiceId serviceId = std::get<UInt32>(eNodeId.nodeId.value);

    auto& serv = services[static_cast<DataTypeId>(serviceId)];
    if (not serv)
    {
        LM(UASRV, LE, "Unexpected service id(%u)", serviceId);
        return;
    }

    serv->receive(msgReq.hdr, rx);
}

} // namespace app::ua::service
