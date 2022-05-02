#pragma once

#include "DataType.hpp"

namespace app::ua
{

using DateTime = NumericType<DataTypeId::DateTime, std::int64_t>;

} // namespace app::ua
