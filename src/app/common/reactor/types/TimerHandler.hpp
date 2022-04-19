#pragma once

#include <functional>

namespace reactor
{

using TimerHandler = std::function<void(void)>;

} // namespace reactor
