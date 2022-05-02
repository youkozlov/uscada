#pragma once

#include "NodeId.hpp"
#include "NodeClassBase.hpp"

namespace app::ua
{

class NodeClassVariable : public NodeClassBase
{
public:
    NodeClassVariable() {}
    ~NodeClassVariable() {}

    Attribute<AttributeId::NodeId, NodeId> value;
    Attribute<AttributeId::NodeId, NodeId> dataType;

private:

};

} // namespace app::ua
