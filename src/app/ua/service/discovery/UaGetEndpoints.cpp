#include "UaGetEndpoints.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaGetEndpointsReq.hpp"
#include "UaGetEndpointsRsp.hpp"
#include "TimeUtils.hpp"
#include "UaServiceSender.hpp"

namespace app::ua::service
{

UaGetEndpoints::UaGetEndpoints()
{
}

UaGetEndpoints::~UaGetEndpoints()
{
}

void UaGetEndpoints::receive(UaEncodedMessageHdr const& hdr, OpcUaSduBuffer& rx)
{
    OpcUaBinaryCodec rxCodec(rx);
    UaGetEndpointsReq req;
    rxCodec >> req;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec txCodec(tx);

    UaGetEndpointsRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.requestHdr.requestHandle;
    auto& descr = rsp.msg.endpointDescription.emplace_back();
    descr.endpointUrl = "opc.tcp://localhost:4369";
    descr.server.applicationUri = "urn:youkozlov-VivoBook-ASUSLaptop-X513EAN-K513EA:uscada";
    descr.server.productUri = "urn:uscada";
    descr.securityMode = toInt32(UaSecurityModeEnum::none);
    descr.securityPolicyUri = "http://opcfoundation.org/UA/SecurityPolicy#None";
    txCodec << rsp;

    reactor::MsgStore<MsgUaEncodedMessageSendReq> msgStore;
    auto& msgRsp = msgStore.getMsg();
    msgRsp.hdr = hdr;
    msgRsp.length = tx.size();
    std::memcpy(&msgRsp.data[0], tx.begin(), tx.size());
    Sender::sendMsg(msgStore);
}

} // namespace app::ua::service
