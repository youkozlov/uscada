#pragma once

#include <functional>

namespace app::reactor
{

enum class LinkEvent
{
      connected
    , data
    , error
};

using LinkHandler = std::function<void(LinkEvent)>;

} // namespace app::reactor
