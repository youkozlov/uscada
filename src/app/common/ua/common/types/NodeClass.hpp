#pragma once

namespace ua
{

enum class NodeClass
{
      Unspecified = 0
    , Object = 1
    , Variable = 2
    , Method = 4
    , ObjectType = 8
    , VariableType = 16
    , ReferenceType = 32
    , DataType = 64
    , View = 128
};

} // namespace ua
