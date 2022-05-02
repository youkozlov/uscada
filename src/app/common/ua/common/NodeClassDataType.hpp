#pragma once

#include "NodeClassBase.hpp"
#include "Boolean.hpp"

namespace app::ua
{

class NodeClassDataType : public NodeClassBase
{
public:
    NodeClassDataType() {}
    ~NodeClassDataType() {}

    Attribute<AttributeId::IsAbstract, Boolean> isAbstract;

};

} // namespace app::ua
