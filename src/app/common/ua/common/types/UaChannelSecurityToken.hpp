#pragma once

#include "UInt32.hpp"
#include "UtcTime.hpp"

namespace app::ua
{

struct UaChannelSecurityToken
{
    UInt32                  secureChannelId;
    UInt32                  tokenId;
    UtcTime                 createdAt;
    UInt32                  revisedLifetime;
};

} // namespace app::ua
