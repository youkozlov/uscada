#pragma once

#include "UaGetEndpoints.hpp"

namespace app::ua::service
{

class UaService;

class UaDiscoveryService
{
public:
    UaDiscoveryService();

    ~UaDiscoveryService();

    void subscribe(UaService&);

private:
};

} // namespace app::ua::service
