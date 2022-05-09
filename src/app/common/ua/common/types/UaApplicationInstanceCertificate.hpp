#pragma once

#include "String.hpp"
#include "ByteString.hpp"
#include "UtcTime.hpp"

namespace app::ua
{
/*
struct UaApplicationInstanceCertificate
{
    String                  version;
    ByteString              serialNumber;
    String                  signatureAlgorithm;
    ByteString              signature;
    String                  issuer;//?
    UtcTime                 validFrom;
    UtcTime                 validTo;
    String                  subject;//?
    String                  applicationUri;
    DynamicArray<String>    hostnames;
    String                  publicKey;
    DynamicArray<String>    keyUsage;
};
*/
using UaApplicationInstanceCertificate = ByteString;

} // namespace app::ua
