#pragma once

#include "DataType.hpp"
#include <string>

namespace ua
{

struct ByteString : public StringType<DataTypeId::ByteString>
{
    using StringType::StringType;
};

} // namespace ua
