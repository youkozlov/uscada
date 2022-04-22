#pragma once

#include <memory>
#include <functional>

namespace reactor
{

class LinkInterface;

using LinkPtr = std::unique_ptr<LinkInterface, std::function<void(LinkInterface*)>>;

} // namespace reactor
