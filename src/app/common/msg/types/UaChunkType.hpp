#pragma once

#include <cstdint>

namespace app
{

enum class UaChunkTypeEnum : std::uint8_t
{
      invalid
    , intermediate
    , final
    , abort
};

struct UaChunkType
{
    using enum UaChunkTypeEnum;
    UaChunkTypeEnum val;

    std::uint8_t toUint8() const
    {
        switch (val)
        {
        case UaChunkType::intermediate:     return 'C';
        case UaChunkType::final:            return 'F';
        case UaChunkType::abort:            return 'A';
        default:                            return 0x0;
        }
        return 0x0;
    }
    static UaChunkType fromUint8(std::uint8_t val)
    {
        switch (val)
        {
        case 'C':   return {UaChunkType::intermediate};
        case 'F':   return {UaChunkType::final};
        case 'A':   return {UaChunkType::abort};
        default:    return {UaChunkType::invalid};
        }
    }
};



} // namespace app
