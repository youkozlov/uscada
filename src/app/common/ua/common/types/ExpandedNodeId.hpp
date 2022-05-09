#pragma once

#include "DataType.hpp"
#include "NodeId.hpp"
#include "String.hpp"
#include "UInt32.hpp"

namespace app::ua
{

struct ExpandedNodeId : public StructType<DataTypeId::ExpandedNodeId>
{
    NodeId      nodeId;
    Opt<String> namespaceUri;
    Opt<UInt32> serverIndex;

    bool operator==(ExpandedNodeId const& rhs) const
    {
        return this->nodeId == rhs.nodeId
            && this->namespaceUri == rhs.namespaceUri
            && this->serverIndex == rhs.serverIndex;
    }
    std::uint8_t encodingMask() const
    {
        return encodeMaskSizeCheck
        (
              namespaceUri
            , serverIndex
        );
    }
};

} // namespace app::ua
