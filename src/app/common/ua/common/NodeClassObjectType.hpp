#pragma once

#include "DataType.hpp"
#include "NodeClassBase.hpp"
#include "Boolean.hpp"

namespace app::ua
{

class NodeClassObjectType : public NodeClassBase
{
public:
    NodeClassObjectType() {}
    ~NodeClassObjectType() {}

    Attribute<AttributeId::IsAbstract, Boolean> isAbstract;
};

using NodeClassObjectTypePtr = std::shared_ptr<NodeClassObjectType>;

} // namespace app::ua
