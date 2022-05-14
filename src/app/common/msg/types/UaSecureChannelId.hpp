#pragma once

#include "EntityId.hpp"

namespace app
{

using UaSecureChannelId = EntityId;

static constexpr UaSecureChannelId invalidScuid = 0x7FFFFFFF;

inline bool isScuidInvalid(UaSecureChannelId val)
{
    return val == invalidScuid;
}

} // namespace app
