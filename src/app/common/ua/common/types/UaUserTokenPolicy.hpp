#pragma once

#include "String.hpp"
#include "UaUserTokenType.hpp"
#include "String.hpp"

namespace app::ua
{

struct UaUserTokenPolicy
{
    String                  policyId;
    UaUserTokenType         tokenType;
    String                  issuedTokenType;
    String                  issuerEndpointUrl;
    String                  securityPolicyUri;
};

} // namespace app::ua
