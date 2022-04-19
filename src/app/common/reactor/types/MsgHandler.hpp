#pragma once

#include <functional>

namespace reactor
{

struct MsgInterface;

using MsgHandler = std::function<void(MsgInterface const&)>;

} // namespace reactor
