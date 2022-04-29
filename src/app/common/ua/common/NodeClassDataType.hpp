#pragma once

#include "NodeClassBase.hpp"
#include "Boolean.hpp"

namespace ua
{

class NodeClassDataType : public NodeClassBase
{
public:
    NodeClassDataType() {}
    ~NodeClassDataType() {}

    Attribute<AttributeId::IsAbstract, Boolean> isAbstract;

};

} // namespace ua
