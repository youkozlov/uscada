#pragma once

#include <cstdint>

namespace app
{

template <typename TYPE>
static TYPE fromUint8(std::uint8_t val)
{
    return static_cast<TYPE>(val);
}

} // namespace app
