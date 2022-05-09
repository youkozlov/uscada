#pragma once

#include "String.hpp"
#include "LocalizedText.hpp"
#include "UaApplicationType.hpp"
#include "String.hpp"

namespace app::ua
{

struct UaApplicationDescription
{
    String                  applicationUri;
    String                  productUri;
    LocalizedText           applicationName;
    UaApplicationType       applicationType;
    String                  gatewayServerUri;
    String                  discoveryProfileUri;
    DynamicArray<String>    discoveryUrls;
};

} // namespace app::ua
