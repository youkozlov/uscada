#pragma once

#include <string>
#include "DataType.hpp"

namespace app::ua
{

struct String : public StringType<DataTypeId::String>
{
    using StringType::StringType;
};

} // namespace app::ua
