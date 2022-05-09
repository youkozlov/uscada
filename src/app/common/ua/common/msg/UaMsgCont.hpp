#pragma once

#include "ExpandedNodeId.hpp"

namespace app::ua
{

template <typename DataType, DataTypeId Id>
struct UaMsgCont
{
    UaMsgCont()
    {
        eNodeId.nodeId.value.template emplace<UInt32>(static_cast<std::uint32_t>(Id));
    }
    ExpandedNodeId eNodeId;
    DataType msg;
};

} // namespace app::ua
