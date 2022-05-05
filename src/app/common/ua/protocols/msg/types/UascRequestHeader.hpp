#pragma once

#include "UascSessionAuthentificationToken.hpp"
#include "UtcTime.hpp"
#include "UInt32.hpp"
#include "String.hpp"
#include "Boolean.hpp"

namespace app::ua
{

struct UascRequestHeader
{
    UascSessionAuthentificationToken    authentificationToken;
    UtcTime                             timestamp;
    UInt32                              requestHandle;
    UInt32                              returnDignostics;
    String                              auditEntityId;
    UInt32                              timeoutHint;
    Boolean                             isOnline;
};

} // namespace app::ua
