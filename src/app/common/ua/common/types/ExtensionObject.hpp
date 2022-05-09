#pragma once

#include "DataType.hpp"
#include "ByteString.hpp"
#include "XmlElement.hpp"

namespace app::ua
{

struct ExtensionObject : public StructType<DataTypeId::ExtensionObject>
{
    NodeId nodeId;
    Opt<ByteString> byteString;

    bool operator==(ExtensionObject const& rhs) const
    {
        return this->nodeId == rhs.nodeId
            && this->byteString == rhs.byteString;
    }
    std::uint8_t encodingMask() const
    {
        return encodeMaskSizeCheck
        (
              byteString
        );
    }
};

} // namespace app::ua
