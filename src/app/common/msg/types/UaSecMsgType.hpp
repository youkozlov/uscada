#pragma once

#include <string>

namespace app
{

enum class UaSecMsgType
{
      invalid
    , opn
    , clo
    , msg
};

inline std::string toString(UaSecMsgType val)
{
    switch (val)
    {
    case UaSecMsgType::opn: return "opn";
    case UaSecMsgType::clo: return "clo";
    case UaSecMsgType::msg: return "msg";
    default:
    case UaSecMsgType::invalid: return "invalid";
    }
}

} // namespace app
