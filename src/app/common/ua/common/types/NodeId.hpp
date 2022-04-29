#pragma once

#include "StructType.hpp"
#include "UInt16.hpp"
#include "UInt32.hpp"
#include "String.hpp"
#include "Guid.hpp"
#include "Opaque.hpp"

namespace ua
{

struct NodeId : public StructType<DataTypeId::NodeId>
{
    UInt16 namespaceIndex;
    Var<
          UInt32
        , String
        , Guid
        , Opaque
    > value;

    bool operator==(NodeId const& rhs) const
    {
        return this->namespaceIndex == rhs.namespaceIndex
            && this->value == rhs.value;
    }
};

} // namespace ua
