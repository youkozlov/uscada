#pragma once

#include <string>
#include "DataType.hpp"

namespace ua
{

struct String : public StringType<DataTypeId::String>
{
    using StringType::StringType;
};

} // namespace ua
