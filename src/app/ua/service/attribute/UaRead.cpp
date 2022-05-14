#include "UaRead.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaAttributeService.hpp"
#include "UaReadReq.hpp"
#include "UaReadRsp.hpp"

namespace app::ua::service
{

UaRead::UaRead(UaAttributeService& attributeService_)
    : attributeService(attributeService_)
{
}

UaRead::~UaRead()
{
}

void UaRead::receive(UaEncodedMessageHdr const& hdr, OpcUaSduBuffer& rx)
{
    OpcUaBinaryCodec codec(rx);
    UaReadReq req;
    codec >> req;

    attributeService.receive(hdr, req);
}

} // namespace app::ua::service
