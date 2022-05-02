#pragma once

#include <memory>
#include <functional>

namespace app::reactor
{

class LinkInterface;

using LinkPtr = std::unique_ptr<LinkInterface, std::function<void(LinkInterface*)>>;

} // namespace app::reactor
