#pragma once

#include "DataType.hpp"
#include <string>

namespace app::ua
{

struct ByteString : public StringType<DataTypeId::ByteString>
{
    using StringType::StringType;
};

} // namespace app::ua
