#include "OpcUaBinaryStream.hpp"
#include "Logger.hpp"

#include <cstring>

namespace ua
{

OpcUaBinaryStream::OpcUaBinaryStream()
    : begin(0)
    , end(0)
{
}

OpcUaBinaryStream::~OpcUaBinaryStream()
{
}

void OpcUaBinaryStream::write(std::uint8_t val)
{
    LM(GEN, LD, "end: %u, wr: %d", end, (int)val);
    packet[end++] = val;
}

std::uint8_t OpcUaBinaryStream::read()
{
    auto const& rd = packet[begin];
    LM(GEN, LD, "begin: %u, rd: %d", begin, (int)rd);
    begin++;
    return rd;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Undefined&)
{
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Undefined const&)
{
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Boolean& val)
{
    val = s.read() ? true : false;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Boolean const& val)
{
    s.write(val ? 0x1 : 0x0);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, SByte& val)
{
    val = s.read();
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, SByte const& val)
{
    s.write(val);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Byte& val)
{
    val = s.read();
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Byte const& val)
{
    s.write(val);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Int16& val)
{
    std::uint16_t const ll = s.read();
    std::uint16_t const hh = s.read();
    val = hh << 8 | ll;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Int16 const& val)
{
    s.write(val);
    s.write(val >> 8);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, UInt16& val)
{
    std::uint16_t const ll = s.read();
    std::uint16_t const hh = s.read();
    val = hh << 8 | ll;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, UInt16 const& val)
{
    s.write(val);
    s.write(val >> 8);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Int32& val)
{
    std::uint32_t const a = s.read();
    std::uint32_t const b = s.read();
    std::uint32_t const c = s.read();
    std::uint32_t const d = s.read();
    val = d << 24 | c << 16 | b << 8 | a;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Int32 const& val)
{
    s.write(val);
    s.write(val >> 8);
    s.write(val >> 16);
    s.write(val >> 24);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, UInt32& val)
{
    std::uint32_t const a = s.read();
    std::uint32_t const b = s.read();
    std::uint32_t const c = s.read();
    std::uint32_t const d = s.read();
    val = d << 24 | c << 16 | b << 8 | a;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, UInt32 const& val)
{
    s.write(val);
    s.write(val >> 8);
    s.write(val >> 16);
    s.write(val >> 24);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Int64& val)
{
    std::uint64_t const a = s.read();
    std::uint64_t const b = s.read();
    std::uint64_t const c = s.read();
    std::uint64_t const d = s.read();
    std::uint64_t const e = s.read();
    std::uint64_t const f = s.read();
    std::uint64_t const g = s.read();
    std::uint64_t const h = s.read();
    val = h << 56 | g << 48 | f << 40 | e << 32 | d << 24 | c << 16 | b << 8 | a;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Int64 const& val)
{
    s.write(val);
    s.write(val >> 8);
    s.write(val >> 16);
    s.write(val >> 24);
    s.write(val >> 32);
    s.write(val >> 40);
    s.write(val >> 48);
    s.write(val >> 56);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, UInt64& val)
{
    std::uint64_t const a = s.read();
    std::uint64_t const b = s.read();
    std::uint64_t const c = s.read();
    std::uint64_t const d = s.read();
    std::uint64_t const e = s.read();
    std::uint64_t const f = s.read();
    std::uint64_t const g = s.read();
    std::uint64_t const h = s.read();
    val = h << 56 | g << 48 | f << 40 | e << 32 | d << 24 | c << 16 | b << 8 | a;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, UInt64 const& val)
{
    s.write(val);
    s.write(val >> 8);
    s.write(val >> 16);
    s.write(val >> 24);
    s.write(val >> 32);
    s.write(val >> 40);
    s.write(val >> 48);
    s.write(val >> 56);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Float& val)
{
    std::uint32_t const a = s.read();
    std::uint32_t const b = s.read();
    std::uint32_t const c = s.read();
    std::uint32_t const d = s.read();
    std::uint32_t const comb = d << 24 | c << 16 | b << 8 | a;
    float tmp{val};
    std::memcpy(&tmp, &comb, sizeof(std::uint32_t));
    val = tmp;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Float const& val)
{
    std::uint32_t comb;
    float tmp{val};
    std::memcpy(&comb, &tmp, sizeof(std::uint32_t));
    s.write(comb);
    s.write(comb >> 8);
    s.write(comb >> 16);
    s.write(comb >> 24);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Double& val)
{
    std::uint64_t const a = s.read();
    std::uint64_t const b = s.read();
    std::uint64_t const c = s.read();
    std::uint64_t const d = s.read();
    std::uint64_t const e = s.read();
    std::uint64_t const f = s.read();
    std::uint64_t const g = s.read();
    std::uint64_t const h = s.read();
    std::uint64_t const comb = h << 56 | g << 48 | f << 40 | e << 32 | d << 24 | c << 16 | b << 8 | a;
    double tmp{val};
    std::memcpy(&tmp, &comb, sizeof(std::uint64_t));
    val = tmp;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Double const& val)
{
    std::uint64_t comb;
    double tmp{val};
    std::memcpy(&comb, &tmp, sizeof(std::uint64_t));
    s.write(comb);
    s.write(comb >> 8);
    s.write(comb >> 16);
    s.write(comb >> 24);
    s.write(comb >> 32);
    s.write(comb >> 40);
    s.write(comb >> 48);
    s.write(comb >> 56);
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, String& val)
{
    Int32 len;
    s >> len;
    if (len == -1)
    {
        return s;
    }
    val.resize(len);
    for (std::int32_t i = 0; i < len; ++i)
    {
        val[i] = s.read();
    }
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, String const& val)
{
    Int32 len;
    len = val.size();
    if (len == 0)
    {
        len = -1;
        s << len;
        return s;
    }
    s << len;
    for (std::int32_t i = 0; i < len; ++i)
    {
        s.write(val[i]);
    }
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, DateTime& val)
{
    Int64 tmpl;
    s >> tmpl;
    val = tmpl;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, DateTime const& val)
{
    Int64 tmpl{val};
    s << tmpl;
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Guid& val)
{
    s >> val.data1;
    s >> val.data2;
    s >> val.data3;
    s >> val.data4;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Guid const& val)
{
    s << val.data1;
    s << val.data2;
    s << val.data3;
    s << val.data4;
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, ByteString& val)
{
    Int32 len;
    s >> len;
    if (len == -1)
    {
        val.clear();
        return s;
    }
    val.resize(len);
    for (std::int32_t i = 0; i < len; ++i)
    {
        val[i] = s.read();
    }
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, ByteString const& val)
{
    Int32 len;
    len = val.size();
    if (len == 0)
    {
        len = -1;
        s << len;
        return s;
    }
    s << len;
    for (std::int32_t i = 0; i < len; ++i)
    {
        s.write(val[i]);
    }
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, NodeId& nodeId)
{
    Byte encByte;
    s >> encByte;
    switch (encByte)
    {
    case 0:
    {
        Byte identifier;
        s >> identifier;
        nodeId.value.emplace<UInt32>(identifier);
    }
    break;
    case 1:
    {
        Byte namespaceIndex;
        UInt16 identifier;
        s >> namespaceIndex >> identifier;
        nodeId.namespaceIndex = namespaceIndex;
        nodeId.value.emplace<UInt32>(identifier);
    }
    break;
    case 2:
    {
        s >> nodeId.namespaceIndex >> nodeId.value.emplace<UInt32>();
    }
    break;
    case 3:
    {
        s >> nodeId.namespaceIndex >> nodeId.value.emplace<String>();
    }
    break;
    case 4:
    {
        s >> nodeId.namespaceIndex >> nodeId.value.emplace<Guid>();
    }
    break;
    case 5:
    {
        s >> nodeId.namespaceIndex >> nodeId.value.emplace<Opaque>();
    }
    break;
    default:
        throw;
    }
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, NodeId const& nodeId)
{
    if (std::holds_alternative<UInt32>(nodeId.value))
    {
        UInt32 const& identifier = std::get<UInt32>(nodeId.value);
        if (nodeId.namespaceIndex == 0 && identifier < 256)
        {
            Byte encByte{0};
            Byte encCastValue{static_cast<Byte::Type>(identifier)};
            s << encByte << encCastValue;
        }
        else if (nodeId.namespaceIndex < 256 && identifier < 65536)
        {
            Byte encByte{1};
            Byte namespaceIndex{static_cast<Byte::Type>(nodeId.namespaceIndex)};
            UInt16 encCastValue{static_cast<UInt16::Type>(identifier)};
            s << encByte << namespaceIndex << encCastValue;
        }
        else
        {
            Byte encByte{2};
            s << encByte << nodeId.namespaceIndex << identifier;
        }
    }
    else if (std::holds_alternative<String>(nodeId.value))
    {
        Byte encByte{3};
        s << encByte << nodeId.namespaceIndex << std::get<String>(nodeId.value);
    }
    else if (std::holds_alternative<Guid>(nodeId.value))
    {
        Byte encByte{4};
        s << encByte << nodeId.namespaceIndex << std::get<Guid>(nodeId.value);
    }
    else if (std::holds_alternative<Opaque>(nodeId.value))
    {
        Byte encByte{5};
        s << encByte << nodeId.namespaceIndex << std::get<Opaque>(nodeId.value);
    }
    else
    {
        throw;
    }
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, StatusCode& statusCode)
{
    UInt32 tmpl;
    s >> tmpl;
    statusCode = tmpl;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, StatusCode const& statusCode)
{
    UInt32 tmpl{statusCode};
    s << tmpl;
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, DiagnosticInfo& diagInfo)
{
    Byte encodingMask;
    s >> encodingMask;
    if (encodingMask & 0x1)
    {
        s >> diagInfo.symbolicId;
    }
    if (encodingMask & 0x2)
    {
        s >> diagInfo.namespaceUri;
    }
    if (encodingMask & 0x4)
    {
        s >> diagInfo.locale;
    }
    if (encodingMask & 0x8)
    {
        s >> diagInfo.localizedText;
    }
    if (encodingMask & 0x10)
    {
        s >> diagInfo.additionalInfo;
    }
    if (encodingMask & 0x20)
    {
        s >> diagInfo.innerStatusCode;
    }
    if (encodingMask & 0x40)
    {
        s >> diagInfo.innerDiagnosticInfo;
    }
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, DiagnosticInfo const& diagInfo)
{
    Byte encodingMask{diagInfo.encodingMask()};
    s << encodingMask;
    if (encodingMask & 0x1)
    {
        s << diagInfo.symbolicId;
    }
    if (encodingMask & 0x2)
    {
        s << diagInfo.namespaceUri;
    }
    if (encodingMask & 0x4)
    {
        s << diagInfo.locale;
    }
    if (encodingMask & 0x8)
    {
        s << diagInfo.localizedText;
    }
    if (encodingMask & 0x10)
    {
        s << diagInfo.additionalInfo;
    }
    if (encodingMask & 0x20)
    {
        s << diagInfo.innerStatusCode;
    }
    if (encodingMask & 0x40)
    {
        s << diagInfo.innerDiagnosticInfo;
    }
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, QualifiedName& qn)
{
    s >> qn.namespaceIndex >> qn.name;
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, QualifiedName const& qn)
{
    s << qn.namespaceIndex << qn.name;
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, LocalizedText& lt)
{
    Byte encodingMask;
    s >> encodingMask;
    if (encodingMask & 0x1)
    {
        s >> lt.locale;
    }
    if (encodingMask & 0x2)
    {
        s >> lt.text;
    }
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, LocalizedText const& lt)
{
    Byte encodingMask{lt.encodingMask()};
    s << encodingMask;

    if ((encodingMask & 0x1) && lt.locale->size())
    {
        s << lt.locale;
    }
    if ((encodingMask & 0x2) && lt.text->size())
    {
        s << lt.text;
    }
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, XmlElement&)
{
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, XmlElement const&)
{
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, ExpandedNodeId&)
{
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, ExpandedNodeId const&)
{
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, ExtensionObject&)
{
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, ExtensionObject const&)
{
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, DataValue& data)
{
    Byte encodingMask;
    s >> encodingMask;
    if (encodingMask & 0x1)
    {
        s >> data.value;
    }
    if (encodingMask & 0x2)
    {
        s >> data.status;
    }
    if (encodingMask & 0x4)
    {
        s >> data.sourceTimestampt;
    }
    if (encodingMask & 0x8)
    {
        s >> data.sourcePicoSeconds;
    }
    if (encodingMask & 0x10)
    {
        s >> data.serverTimeStampt;
    }
    if (encodingMask & 0x20)
    {
        s >> data.serverPicoSeconds;
    }
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, DataValue const& data)
{
    Byte encodingMask{data.encodingMask()};
    s << encodingMask;
    if (encodingMask & 0x1)
    {
        s << data.value;
    }
    if (encodingMask & 0x2)
    {
        s << data.status;
    }
    if (encodingMask & 0x4)
    {
        s << data.sourceTimestampt;
    }
    if (encodingMask & 0x8)
    {
        s << data.sourcePicoSeconds;
    }
    if (encodingMask & 0x10)
    {
        s << data.serverTimeStampt;
    }
    if (encodingMask & 0x20)
    {
        s << data.serverPicoSeconds;
    }
    return s;
}

OpcUaBinaryStream& operator>>(OpcUaBinaryStream& s, Variant& variant)
{
    Byte encodingMask;
    s >> encodingMask;
    if (0 == encodingMask)
    {
        return s;
    }
    DataTypeId const typeId = static_cast<DataTypeId>(encodingMask & 0b111111);
    if (encodingMask & 0x80)
    {
        s >> variant.arrayLength.emplace();
        switch (typeId)
        {
        case DataTypeId::Boolean:
        {
            s >> emplace<Boolean>(variant, *variant.arrayLength);
        }
        break;
        case DataTypeId::SByte:
        {
            s >> emplace<SByte>(variant, *variant.arrayLength);
        }
        break;
        case DataTypeId::Byte:
        {
            s >> emplace<Byte>(variant, *variant.arrayLength);
        }
        break;
        case DataTypeId::Int16:
        {
            s >> emplace<Int16>(variant, *variant.arrayLength);
        }
        break;
        case DataTypeId::UInt16:
        {
            s >> emplace<UInt16>(variant, *variant.arrayLength);
        }
        break;
        case DataTypeId::Int32:
        {
            s >> emplace<Int32>(variant, *variant.arrayLength);
        }
        break;
        case DataTypeId::UInt32:
        {
            s >> emplace<UInt32>(variant, *variant.arrayLength);
        }
        break;
        default:
            throw;
        }
        return s;
    }
    else
    {
        switch (typeId)
        {
        case DataTypeId::Undefined:
        break;
        case DataTypeId::Boolean:
        {
            s >> emplace<Boolean>(variant);
        }
        break;
        case DataTypeId::SByte:
        {
            s >> emplace<SByte>(variant);
        }
        break;
        case DataTypeId::Byte:
        {
            s >> emplace<Byte>(variant);
        }
        break;
        case DataTypeId::Int16:
        {
            s >> emplace<Int16>(variant);
        }
        break;
        case DataTypeId::UInt16:
        {
            s >> emplace<UInt16>(variant);
        }
        break;
        case DataTypeId::Int32:
        {
            s >> emplace<Int32>(variant);
        }
        break;
        case DataTypeId::UInt32:
        {
            s >> emplace<UInt32>(variant);
        }
        break;
        case DataTypeId::Int64:
        {
            s >> emplace<Int64>(variant);
        }
        break;
        case DataTypeId::UInt64:
        {
            s >> emplace<UInt64>(variant);
        }
        break;
        case DataTypeId::Float:
        {
            s >> emplace<Float>(variant);
        }
        break;
        case DataTypeId::Double:
        {
            s >> emplace<Double>(variant);
        }
        break;
        case DataTypeId::String:
        {
            s >> emplace<String>(variant);
        }
        break;
        case DataTypeId::DateTime:
        {
            s >> emplace<DateTime>(variant);
        }
        break;
        case DataTypeId::Guid:
        {
            s >> emplace<Guid>(variant);
        }
        break;
        case DataTypeId::ByteString:
        {
            s >> emplace<ByteString>(variant);
        }
        break;
        case DataTypeId::XmlElement:
        {
            s >> emplace<XmlElement>(variant);
        }
        break;
        case DataTypeId::NodeId:
        {
            s >> emplace<NodeId>(variant);
        }
        break;
        case DataTypeId::ExpandedNodeId:
        {
            s >> emplace<ExpandedNodeId>(variant);
        }
        break;
        case DataTypeId::StatusCode:
        {
            s >> emplace<StatusCode>(variant);
        }
        break;
        case DataTypeId::QualifiedName:
        {
            s >> emplace<QualifiedName>(variant);
        }
        break;
        case DataTypeId::LocalizedText:
        {
            s >> emplace<LocalizedText>(variant);
        }
        break;
        case DataTypeId::ExtensionObject:
        {
            s >> emplace<ExtensionObject>(variant);
        }
        break;
        case DataTypeId::DataValue:
        case DataTypeId::Variant:
        case DataTypeId::DiagnosticInfo:
            LM(GEN, LE, "Unexpected");
        break;
        };
    }
    return s;
}

OpcUaBinaryStream& operator<<(OpcUaBinaryStream& s, Variant const& variant)
{
    Byte encodingMask{variant.encodingMask()};
    s << encodingMask;
    if (0 == encodingMask)
    {
        return s;
    }
    if (encodingMask & 0x80)
    {
        s << variant.arrayLength;
    }
    std::visit([&s](auto&& arg)
    {
        s << arg;
    }, variant.value);
    return s;
}

} // namespace ua
