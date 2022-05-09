#include "UaRead.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaAttributeController.hpp"
#include "UaReadReq.hpp"
#include "UaReadRsp.hpp"

namespace app::ua
{

UaRead::UaRead(UaAttributeController& attributeController_)
    : attributeController(attributeController_)
{
}

UaRead::~UaRead()
{
}

void UaRead::process(OpcUaSecureChannel& channel)
{
    OpcUaBinaryCodec codec(channel.getRxBuffer());
    UaReadReq req;
    codec >> req;

    attributeController.receive(req, [&channel](auto const& rsp) { channel.send(rsp); });
}

} // namespace app::ua
