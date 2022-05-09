#pragma once

#include "UaSessionAuthentificationToken.hpp"
#include "UtcTime.hpp"
#include "UInt32.hpp"
#include "String.hpp"
#include "Boolean.hpp"
#include "UaAdditionalHeader.hpp"

namespace app::ua
{

struct UaRequestHeader
{
    UaSessionAuthentificationToken      authentificationToken;
    UtcTime                             timestamp;
    UInt32                              requestHandle;
    UInt32                              returnDignostics;
    String                              auditEntityId;
    UInt32                              timeoutHint;
    UaAdditionalHeader                  additionalHeader;
};

} // namespace app::ua
