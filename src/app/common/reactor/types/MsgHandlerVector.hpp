#pragma once

#include <vector>
#include <tuple>
#include "MsgId.hpp"
#include "MsgHandler.hpp"

namespace app::reactor
{

using MsgHandlerVector = std::vector<std::tuple<MsgId, MsgHandler>>;

} // namespace app::reactor
