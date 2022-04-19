#pragma once

namespace reactor
{

struct LinkAddr
{
    enum class Type
    {
          ipv4
    };
    Type type;
    char addr[];
};

} // namespace app
