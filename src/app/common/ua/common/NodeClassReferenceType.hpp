#pragma once

#include "DataType.hpp"
#include "NodeClassBase.hpp"
#include "Boolean.hpp"
#include "Attribute.hpp"
#include "LocalizedText.hpp"

namespace ua
{

class NodeClassReferenceType : public NodeClassBase
{
public:
    NodeClassReferenceType() {}
    ~NodeClassReferenceType() {}

    Attribute<AttributeId::IsAbstract, Boolean> isAbstract;
    Attribute<AttributeId::Symmetric, Boolean> symmetric;
    AttributeOpt<AttributeId::InverseName, LocalizedText> inverseName;

    
};

} // namespace ua
