#pragma once

#include <functional>

namespace app::reactor
{

using TimerHandler = std::function<void()>;

} // namespace app::reactor
