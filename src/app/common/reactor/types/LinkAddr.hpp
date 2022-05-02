#pragma once

#include <string>

namespace app::reactor
{

struct LinkAddr
{
    enum class Type
    {
          ipv4
    };
    Type type;
    char data[16];
};

inline std::uint16_t ipv4port(LinkAddr const& addr)
{
    std::uint16_t a = addr.data[4];
    std::uint16_t b = addr.data[5];
    return a << 8 | b;
}

inline std::uint32_t ipv4addr(LinkAddr const& addr)
{
    std::uint32_t a = addr.data[0];
    std::uint32_t b = addr.data[1];
    std::uint32_t c = addr.data[2];
    std::uint32_t d = addr.data[3];
    return a << 24 | b << 16 | c << 8 | d;
}

} // namespace app
