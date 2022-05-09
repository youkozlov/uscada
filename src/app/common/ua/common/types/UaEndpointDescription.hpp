#pragma once

#include "String.hpp"
#include "UaSecurityMode.hpp"
#include "UaApplicationDescription.hpp"
#include "UaApplicationInstanceCertificate.hpp"
#include "UaUserTokenPolicy.hpp"
#include "Byte.hpp"

namespace app::ua
{

struct UaEndpointDescription
{
    String                              endpointUrl;
    UaApplicationDescription            server;
    UaApplicationInstanceCertificate    serverCertificate;
    UaSecurityMode                      securityMode;
    String                              securityPolicyUri;
    DynamicArray<UaUserTokenPolicy>     userIdentityTokens;
    String                              transportProfileUri;
    Byte                                securityLevel;
};

} // namespace app::ua
