#include "UaGetEndpoints.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaGetEndpointsReq.hpp"
#include "UaGetEndpointsRsp.hpp"
#include "TimeUtils.hpp"

namespace app::ua
{

UaGetEndpoints::UaGetEndpoints(/* args */)
{
}

UaGetEndpoints::~UaGetEndpoints()
{
}

void UaGetEndpoints::response(OpcUaSecureChannel& channel)
{
    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);

    UaGetEndpointsRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = storedRequestHandle;
    auto& descr = rsp.msg.endpointDescription.emplace_back();
    descr.endpointUrl = "opc.tcp://localhost:4369";
    descr.server.applicationUri = "urn:youkozlov-VivoBook-ASUSLaptop-X513EAN-K513EA:uscada";
    descr.server.productUri = "urn:uscada";
    descr.securityMode = toInt32(UaSecurityModeEnum::none);
    descr.securityPolicyUri = "http://opcfoundation.org/UA/SecurityPolicy#None";
    codec << rsp;
    channel.send(tx);
}

void UaGetEndpoints::process(OpcUaSecureChannel& channel)
{
    OpcUaBinaryCodec codec(channel.getRxBuffer());
    UaGetEndpointsReq req;
    codec >> req;

    storedRequestHandle = req.requestHdr.requestHandle;

    response(channel);
}

} // namespace app::ua
