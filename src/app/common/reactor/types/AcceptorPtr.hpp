#pragma once

#include <memory>
#include <functional>

namespace app::reactor
{

class AcceptorInterface;

using AcceptorPtr = std::unique_ptr<AcceptorInterface, std::function<void(AcceptorInterface*)>>;

} // namespace app::reactor
