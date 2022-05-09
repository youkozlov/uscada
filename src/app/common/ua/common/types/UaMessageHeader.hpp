#pragma once

#include "MessageHeader.hpp"

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

} // namespace app::ua
