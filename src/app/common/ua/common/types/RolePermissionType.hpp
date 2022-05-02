#pragma once

#include "NodeId.hpp"

namespace app::ua
{

using PermissionType = unsigned;

struct RolePermissionType
{
    NodeId roleId;
    PermissionType permissions;
};

} // namespace app::ua
