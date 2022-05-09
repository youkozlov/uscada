#pragma once

#include "NodeId.hpp"
#include "IntegerId.hpp"
#include "NumericRange.hpp"
#include "QualifiedName.hpp"

namespace app::ua
{

struct ReadValueId
{
    NodeId                              nodeId;
    IntegerId                           attributeId;
    NumericRange                        indexRange;
    QualifiedName                       dataEncoding;
};

} // namespace app::ua
