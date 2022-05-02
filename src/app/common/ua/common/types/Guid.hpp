#pragma once

#include "StructType.hpp"
#include "Byte.hpp"
#include "UInt16.hpp"
#include "UInt32.hpp"

namespace ua
{

struct Guid : public StructType<DataTypeId::Guid>
{
    UInt32 data1;
    UInt16 data2;
    UInt16 data3;
    StaticArray<Byte, 8> data4;

    bool operator==(Guid const& rhs) const
    {
        return this->data1 == rhs.data1
            && this->data2 == rhs.data2
            && this->data3 == rhs.data3
            && this->data4 == rhs.data4;
    }
};

} // namespace ua
