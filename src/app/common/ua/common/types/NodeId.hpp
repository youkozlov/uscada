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
    using Value = Var
    <
      UInt32
    , String
    , Guid
    , Opaque
    >;
    UInt16 namespaceIndex;
    Value value;

    bool operator==(NodeId const& rhs) const
    {
        return this->namespaceIndex == rhs.namespaceIndex
            && this->value == rhs.value;
    }
};

template <typename T>
T& emplace(NodeId::Value& value)
{
    return value.emplace<T>();
}


} // namespace ua
