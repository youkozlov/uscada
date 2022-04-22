#pragma once

#include <memory>
#include <functional>

#include "TimerInterface.hpp"

namespace reactor
{

using TimerPtr = std::unique_ptr<TimerInterface, std::function<void(TimerInterface*)>>;

} // namespace reactor
