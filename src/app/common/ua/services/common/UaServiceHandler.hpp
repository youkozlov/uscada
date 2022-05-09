#pragma once

#include <functional>
#include "OpcUaSduBuffer.hpp"

namespace app::ua
{

using UaServiceHandler = std::function<void(OpcUaSduBuffer const&)>;

} // namespace app::ua
