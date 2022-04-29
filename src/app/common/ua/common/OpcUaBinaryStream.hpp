#pragma once

#include <cstdint>
#include <array>

#include "Undefined.hpp"
#include "Boolean.hpp"
#include "SByte.hpp"
#include "Byte.hpp"
#include "Int16.hpp"
#include "UInt16.hpp"
#include "Int32.hpp"
#include "UInt32.hpp"
#include "Int64.hpp"
#include "UInt64.hpp"
#include "Float.hpp"
#include "Double.hpp"
#include "String.hpp"
#include "DateTime.hpp"
#include "Guid.hpp"
#include "ByteString.hpp"
#include "NodeId.hpp"
#include "StatusCode.hpp"
#include "DiagnosticInfo.hpp"
#include "QualifiedName.hpp"
#include "LocalizedText.hpp"
#include "XmlElement.hpp"
#include "ExpandedNodeId.hpp"
#include "ExtensionObject.hpp"
#include "DataValue.hpp"
#include "Variant.hpp"

namespace ua
{

class OpcUaBinaryStream
{
public:
    explicit OpcUaBinaryStream();

    ~OpcUaBinaryStream();

    void write(std::uint8_t);

    std::uint8_t read();

private:
    static constexpr unsigned maxPacketLen = 4096;

    unsigned begin;
    unsigned end;
    unsigned len;
    std::array<std::uint8_t, maxPacketLen> packet;
};

OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, Undefined&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, Undefined const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, Boolean&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, Boolean const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, SByte&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, SByte const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, Byte&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, Byte const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, Int16&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, Int16 const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, UInt16&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, UInt16 const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, Int32&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, Int32 const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, UInt32&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, UInt32 const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, Int64&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, Int64 const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, UInt64&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, UInt64 const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, Float&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, Float const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, Double&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, Double const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, String&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, String const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, DateTime&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, DateTime const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, Guid&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, Guid const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, ByteString&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, ByteString const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, NodeId&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, NodeId const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, StatusCode&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, StatusCode const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, DiagnosticInfo&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, DiagnosticInfo const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, QualifiedName&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, QualifiedName const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, LocalizedText&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, LocalizedText const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, XmlElement&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, XmlElement const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, ExpandedNodeId&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, ExpandedNodeId const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, ExtensionObject&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, ExtensionObject const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, DataValue&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, DataValue const&);
OpcUaBinaryStream& operator>>(OpcUaBinaryStream&, Variant&);
OpcUaBinaryStream& operator<<(OpcUaBinaryStream&, Variant const&);

template <typename T>
OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Opt<T>& val)
{
    val.emplace();
    s >> *val;
    return s;
}
template <typename T>
OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Opt<T> const& val)
{
    s << val.value();
    return s;
}
template <typename T>
OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Ptr<T>& val)
{
    val = std::make_unique<T>();
    s >> *val;
    return s;
}
template <typename T>
OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Ptr<T> const& val)
{
    s << *val;
    return s;
}
template <typename T, auto SIZE>
OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, StaticArray<T, SIZE>& arr)
{
    for (auto& it : arr)
    {
        s >> it;
    }
    return s;
}
template <typename T, auto SIZE>
OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, StaticArray<T, SIZE> const& arr)
{
    for (auto& it : arr)
    {
        s << it;
    }
    return s;
}
template <typename T>
OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, DynamicArray<T>& arr)
{
    for (auto& it : arr)
    {
        s >> it;
    }
    return s;
}
template <typename T>
OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, DynamicArray<T> const& arr)
{
    for (auto& it : arr)
    {
        s << it;
    }
    return s;
}

} // namespace ua
