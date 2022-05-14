#pragma once

#include "MessageHeader.hpp"
#include "UaSecMsgType.hpp"

namespace app::ua
{

struct UaMessageHeader : public MessageHeader
{
    UInt32                  secureChannelId;
};

inline bool isOpnMsg(std::uint8_t* msg)
{
    return msg[0] == 'O' && msg[1] == 'P' && msg[2] == 'N';
}

inline bool isCloMsg(std::uint8_t* msg)
{
    return msg[0] == 'C' && msg[1] == 'L' && msg[2] == 'O';
}

inline bool isSecMsg(std::uint8_t* msg)
{
    return msg[0] == 'M' && msg[1] == 'S' && msg[2] == 'G';
}

inline std::uint32_t getSecureChannelIdFromHdr(std::uint8_t const* msg)
{
    std::uint32_t const a = msg[8];
    std::uint32_t const b = msg[9];
    std::uint32_t const c = msg[10];
    std::uint32_t const d = msg[11];
    std::uint32_t val = d << 24 | c << 16 | b << 8 | a;
    return val;
}

inline UaSecMsgType fromString(std::uint8_t* msg)
{
    if (0 == std::memcmp(msg, "MSG", 3))
    {
        return UaSecMsgType::msg;
    }
    else if (0 == std::memcmp(msg, "OPN", 3))
    {
        return UaSecMsgType::opn;
    }
    else if (0 == std::memcmp(msg, "CLO", 3))
    {
        return UaSecMsgType::clo;
    }
    return UaSecMsgType::invalid;
}

} // namespace app::ua
