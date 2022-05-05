#pragma once

#include "MessageHeader.hpp"

namespace app::ua
{

struct UascMessageHeader : public MessageHeader
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

} // namespace app::ua
