#pragma once

#include <memory>

namespace reactor
{

class TimerInterface;

using TimerPtr = std::unique_ptr<TimerInterface>;

} // namespace reactor
