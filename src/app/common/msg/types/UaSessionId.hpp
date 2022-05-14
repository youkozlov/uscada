#pragma once

#include <cstdint>

namespace app
{

using UaSessionId = std::uint32_t;

static constexpr UaSecureChannelId invalidSuid = 0x7FFFFFFF;

inline bool isSuidInvalid(UaSessionId val)
{
    return val == invalidSuid;
}

} // namespace app
