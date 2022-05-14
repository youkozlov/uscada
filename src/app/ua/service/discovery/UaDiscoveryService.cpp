#include "UaDiscoveryService.hpp"
#include "UaService.hpp"
#include "UaGetEndpoints.hpp"

namespace app::ua::service
{

UaDiscoveryService::UaDiscoveryService()
{
}

UaDiscoveryService::~UaDiscoveryService()
{
}

void UaDiscoveryService::subscribe(UaService& service)
{
    service.subscribeService(DataTypeId::GetEndpointsRequest_Encoding_DefaultBinary, std::make_unique<UaGetEndpoints>());
}


} // namespace app::ua::service
