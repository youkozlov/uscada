#pragma once

#include <vector>
#include <tuple>
#include "MsgId.hpp"
#include "MsgHandler.hpp"

namespace reactor
{

using MsgHandlerVector = std::vector<std::tuple<MsgId, MsgHandler>>;

} // namespace reactor
