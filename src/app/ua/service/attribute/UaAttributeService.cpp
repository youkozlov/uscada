#include "UaAttributeService.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaRead.hpp"
#include "UaReadReq.hpp"
#include "UaReadRsp.hpp"
#include "UaService.hpp"
#include "UaServiceSender.hpp"
#include "TimeUtils.hpp"

namespace app::ua::service
{

UaAttributeService::UaAttributeService()
{
}

UaAttributeService::~UaAttributeService()
{
}

void UaAttributeService::subscribe(UaService& service)
{
    service.subscribeService(DataTypeId::ReadRequest_Encoding_DefaultBinary, std::make_unique<UaRead>(*this));
}

void UaAttributeService::receive(UaEncodedMessageHdr const& hdr, UaReadReq const& req)
{
    UaReadRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.requestHdr.requestHandle;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    codec << rsp;

    reactor::MsgStore<MsgUaEncodedMessageSendReq> msgStore;
    auto& msgRsp = msgStore.getMsg();
    msgRsp.hdr = hdr;
    msgRsp.length = tx.size();
    std::memcpy(&msgRsp.data[0], tx.begin(), tx.size());
    Sender::sendMsg(msgStore);
}

} // namespace app::ua::service
