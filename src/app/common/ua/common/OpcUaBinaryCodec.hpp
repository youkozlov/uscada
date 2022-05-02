#pragma once

#include <cstdint>
#include <array>

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

namespace app::ua
{

class OpcUaBinaryCodec
{
public:
    explicit OpcUaBinaryCodec();

    ~OpcUaBinaryCodec();

    void write(std::uint8_t);

    std::uint8_t read();

    std::uint8_t const* begin() const;

    std::uint8_t* begin();

    std::uint8_t* end();

    std::uint8_t const* end() const;

    std::uint32_t size() const;

    std::uint32_t capacity() const;

    void seek(std::uint32_t);

    void reset();

private:
    static constexpr unsigned maxPacketLen = 4096;

    unsigned tail;
    unsigned head;
    unsigned len;
    std::array<std::uint8_t, maxPacketLen> packet;
};

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, Boolean&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, Boolean const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, SByte&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, SByte const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, Byte&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, Byte const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, Int16&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, Int16 const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UInt16&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UInt16 const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, Int32&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, Int32 const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UInt32&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UInt32 const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, Int64&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, Int64 const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UInt64&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UInt64 const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, Float&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, Float const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, Double&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, Double const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, String&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, String const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, DateTime&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, DateTime const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, Guid&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, Guid const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, ByteString&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, ByteString const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, NodeId&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, NodeId const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, StatusCode&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, StatusCode const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, DiagnosticInfo&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, DiagnosticInfo const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, QualifiedName&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, QualifiedName const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, LocalizedText&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, LocalizedText const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, XmlElement&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, XmlElement const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, ExpandedNodeId&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, ExpandedNodeId const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, ExtensionObject&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, ExtensionObject const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, DataValue&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, DataValue const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, Variant&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, Variant const&);
template <typename T>
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Opt<T>& val)
{
    val.emplace();
    s >> *val;
    return s;
}
template <typename T>
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Opt<T> const& val)
{
    s << val.value();
    return s;
}
template <typename T>
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Ptr<T>& val)
{
    val = std::make_unique<T>();
    s >> *val;
    return s;
}
template <typename T>
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Ptr<T> const& val)
{
    s << *val;
    return s;
}
template <typename T, auto SIZE>
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, StaticArray<T, SIZE>& arr)
{
    for (auto& it : arr)
    {
        s >> it;
    }
    return s;
}
template <typename T, auto SIZE>
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, StaticArray<T, SIZE> const& arr)
{
    for (auto& it : arr)
    {
        s << it;
    }
    return s;
}
template <typename T>
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, DynamicArray<T>& arr)
{
    for (auto& it : arr)
    {
        s >> it;
    }
    return s;
}
template <typename T>
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, DynamicArray<T> const& arr)
{
    for (auto& it : arr)
    {
        s << it;
    }
    return s;
}

} // namespace app::ua
