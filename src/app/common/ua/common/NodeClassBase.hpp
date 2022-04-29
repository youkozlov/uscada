#pragma once

#include <memory>
#include <map>
#include <string>

#include "Attribute.hpp"
#include "DataType.hpp"
#include "NodeId.hpp"
#include "NodeClass.hpp"
#include "QualifiedName.hpp"
#include "LocalizedText.hpp"
#include "AttributeWriteMask.hpp"
#include "RolePermissionType.hpp"

namespace ua
{

class NodeClassBase
{
public:
    NodeClassBase() {}
    ~NodeClassBase() {}

    Attribute<AttributeId::NodeId, NodeId> nodeId;
    Attribute<AttributeId::NodeClass, NodeClass> nodeClass;
    Attribute<AttributeId::BrowseName, QualifiedName> browseName;
    Attribute<AttributeId::DisplayName, LocalizedText> displayName;
    AttributeOpt<AttributeId::Description, LocalizedText> description;
    AttributeOpt<AttributeId::WriteMask, AttributeWriteMask> writeMask;
    AttributeOpt<AttributeId::UserWriteMask, AttributeWriteMask> userWriteMask;
    AttributeOpt<AttributeId::RolePermissions, RolePermissionType> rolePermissions;
    AttributeOpt<AttributeId::UserRolePermissions, RolePermissionType> userRolePermissions;
};

using NodeClassBasePtr = std::shared_ptr<NodeClassBase>;
using NodeClassBaseMapPtr = std::map<std::string, NodeClassBasePtr>;

} // namespace ua
