#pragma once

#include <functional>

namespace app::reactor
{

struct MsgInterface;

using MsgHandler = std::function<void(MsgInterface const&)>;

} // namespace app::reactor
