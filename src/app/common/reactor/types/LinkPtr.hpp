#pragma once

#include <memory>

namespace reactor
{

class LinkInterface;

using LinkPtr = std::unique_ptr<LinkInterface>;

} // namespace reactor
