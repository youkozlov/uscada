#include "UaAttributeController.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaReadReq.hpp"
#include "UaReadRsp.hpp"
#include "TimeUtils.hpp"

namespace app::ua
{

UaAttributeController::UaAttributeController()
{
}

UaAttributeController::~UaAttributeController()
{
}

void UaAttributeController::receive(UaReadReq const& req, UaServiceHandler handler)
{
    UaReadRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.requestHdr.requestHandle;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    codec << rsp;
    handler(tx);
}

} // namespace app::ua
