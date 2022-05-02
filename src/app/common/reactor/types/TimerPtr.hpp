#pragma once

#include <memory>
#include <functional>

#include "TimerInterface.hpp"

namespace app::reactor
{

using TimerPtr = std::unique_ptr<TimerInterface, std::function<void(TimerInterface*)>>;

} // namespace app::reactor
