#include "UaRead.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaAttributeService.hpp"
#include "UaSessionService.hpp"
#include "UaReadReq.hpp"

namespace app::ua::service
{

UaRead::UaRead(UaAttributeService& attributeService_, UaSessionService& sessionService_)
    : attributeService(attributeService_)
    , sessionService(sessionService_)
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

    sessionService.receive(hdr, [&]()
    {
        attributeService.receive(hdr, req);
    });
}

} // namespace app::ua::service
