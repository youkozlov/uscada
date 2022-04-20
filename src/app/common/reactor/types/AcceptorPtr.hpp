#pragma once

#include <memory>

namespace reactor
{

class AcceptorInterface;

using AcceptorPtr = std::unique_ptr<AcceptorInterface>;

} // namespace reactor
