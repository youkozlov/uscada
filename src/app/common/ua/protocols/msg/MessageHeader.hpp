#pragma once

#include "Byte.hpp"
#include "UInt32.hpp"
#include "MsgUtils.hpp"

namespace app::ua
{

static constexpr std::uint32_t messageHeaderSize = 8;

struct MessageHeader
{
    StaticArray<Byte, 3> messageType;
    StaticArray<Byte, 1> reserved;
    UInt32 messageSize;
};

inline std::uint32_t getMsgSizeFromHdr(std::uint8_t const* msg)
{
    std::uint32_t const a = msg[4];
    std::uint32_t const b = msg[5];
    std::uint32_t const c = msg[6];
    std::uint32_t const d = msg[7];
    std::uint32_t val = d << 24 | c << 16 | b << 8 | a;
    return val;
}

inline void setPayloadSizeToHdr(std::uint8_t* msg, std::uint32_t val)
{
    msg[4] = val;
    msg[5] = val >> 8;
    msg[6] = val >> 16;
    msg[7] = val >> 24;
}

inline bool isMsgHello(std::uint8_t* msg)
{
    return msg[0] == 'H' && msg[1] == 'E' && msg[2] == 'L';
}

inline bool isMsgAck(std::uint8_t* msg)
{
    return msg[0] == 'A' && msg[1] == 'C' && msg[2] == 'K';
}

} // namespace app::ua
