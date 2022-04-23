#pragma once

#include <memory>
#include <functional>

namespace reactor
{

class AcceptorInterface;

using AcceptorPtr = std::unique_ptr<AcceptorInterface, std::function<void(AcceptorInterface*)>>;

} // namespace reactor
