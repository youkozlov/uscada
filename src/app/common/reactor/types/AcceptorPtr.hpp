#pragma once

#include <memory>
#include <functional>
#include "AcceptorInterface.hpp"

namespace app::reactor
{

using AcceptorPtr = std::unique_ptr<AcceptorInterface, std::function<void(AcceptorInterface*)>>;

} // namespace app::reactor
