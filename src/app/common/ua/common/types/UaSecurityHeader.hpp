#pragma once

#include "ByteString.hpp"

namespace app::ua
{

struct UaSecurityHeader
{
    ByteString              securityPolicyUri;
    ByteString              senderCertificate;
    ByteString              receiverCertificateThumbprint;
};

struct UaSecurityTokenHeader
{
    UInt32                  tokenId;
};

} // namespace app::ua
