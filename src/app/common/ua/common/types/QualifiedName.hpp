#pragma once

#include "StructType.hpp"
#include "String.hpp"
namespace ua
{

struct QualifiedName : public StructType<DataTypeId::QualifiedName>
{
    UInt16 namespaceIndex;
    String name;

    bool operator==(QualifiedName const& rhs) const
    {
        return this->namespaceIndex == rhs.namespaceIndex
            && this->name == rhs.name;
    }
};

} // namespace ua
