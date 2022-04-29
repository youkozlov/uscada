#pragma once

#include "NodeId.hpp"

namespace ua
{

using PermissionType = unsigned;

struct RolePermissionType
{
    NodeId roleId;
    PermissionType permissions;
};

} // namespace ua
