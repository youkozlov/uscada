#pragma once

#include "StructType.hpp"
#include "Byte.hpp"
#include "UInt16.hpp"
#include "UInt32.hpp"

namespace ua
{

struct Guid : public StructType<DataTypeId::Guid>
{
   Guid() = default;
   Guid(std::initializer_list<int> il, UInt32::Type d1, UInt16::Type d2, UInt16::Type d3)
       : data1(d1)
       , data2(d2)
       , data3(d3)
   {
        std::size_t counter = 0;
        for (auto& it : il)
        {
            data4[counter++] = it;
        }
   }

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
