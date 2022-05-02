#include "OpcUaBinaryCodec.hpp"
#include "Logger.hpp"

#include <cstring>

namespace ua
{

OpcUaBinaryCodec::OpcUaBinaryCodec()
    : tail(0)
    , head(0)
{
}

OpcUaBinaryCodec::~OpcUaBinaryCodec()
{
}

void OpcUaBinaryCodec::write(std::uint8_t val)
{
    LM(GEN, LE, "end: %u, wr: %d", head, (int)val);
    packet[head++] = val;
}

std::uint8_t OpcUaBinaryCodec::read()
{
    auto const& rd = packet[tail];
    LM(GEN, LE, "tail: %u, rd: %d", tail, (int)rd);
    tail++;
    return rd;
}

std::uint8_t const* OpcUaBinaryCodec::begin() const
{
    return &packet[tail];
}

std::uint8_t* OpcUaBinaryCodec::begin()
{
    return &packet[tail];
}

std::uint8_t* OpcUaBinaryCodec::end()
{
    return &packet[head];
}

std::uint8_t const* OpcUaBinaryCodec::end() const
{
    return &packet[head];
}

std::uint32_t OpcUaBinaryCodec::size() const
{
    return head;
}

std::uint32_t OpcUaBinaryCodec::capacity() const
{
    return maxPacketLen - head;
}

void OpcUaBinaryCodec::seek(std::uint32_t val)
{
    head += val;
}

void OpcUaBinaryCodec::reset()
{
    tail = head = 0;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Boolean& val)
{
    val = s.read() ? true : false;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Boolean const& val)
{
    s.write(val ? 0x1 : 0x0);
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, SByte& val)
{
    val = s.read();
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, SByte const& val)
{
    s.write(val);
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Byte& val)
{
    val = s.read();
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Byte const& val)
{
    s.write(val);
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Int16& val)
{
    std::uint16_t const ll = s.read();
    std::uint16_t const hh = s.read();
    val = hh << 8 | ll;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Int16 const& val)
{
    s.write(val);
    s.write(val >> 8);
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UInt16& val)
{
    std::uint16_t const ll = s.read();
    std::uint16_t const hh = s.read();
    val = hh << 8 | ll;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UInt16 const& val)
{
    s.write(val);
    s.write(val >> 8);
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Int32& val)
{
    std::uint32_t const a = s.read();
    std::uint32_t const b = s.read();
    std::uint32_t const c = s.read();
    std::uint32_t const d = s.read();
    val = d << 24 | c << 16 | b << 8 | a;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Int32 const& val)
{
    s.write(val);
    s.write(val >> 8);
    s.write(val >> 16);
    s.write(val >> 24);
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UInt32& val)
{
    std::uint32_t const a = s.read();
    std::uint32_t const b = s.read();
    std::uint32_t const c = s.read();
    std::uint32_t const d = s.read();
    val = d << 24 | c << 16 | b << 8 | a;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UInt32 const& val)
{
    s.write(val);
    s.write(val >> 8);
    s.write(val >> 16);
    s.write(val >> 24);
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Int64& val)
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

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Int64 const& val)
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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UInt64& val)
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

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UInt64 const& val)
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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Float& val)
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

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Float const& val)
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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Double& val)
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

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Double const& val)
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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, String& val)
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

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, String const& val)
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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, DateTime& val)
{
    Int64 tmpl;
    s >> tmpl;
    val = tmpl;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, DateTime const& val)
{
    Int64 tmpl{val};
    s << tmpl;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Guid& val)
{
    s >> val.data1;
    s >> val.data2;
    s >> val.data3;
    s >> val.data4;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Guid const& val)
{
    s << val.data1;
    s << val.data2;
    s << val.data3;
    s << val.data4;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, ByteString& val)
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

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, ByteString const& val)
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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, NodeId& nodeId)
{
    Byte encByte;
    s >> encByte;
    switch (encByte)
    {
    case 0:
    {
        Byte identifier;
        s >> identifier;
        emplace<UInt32>(nodeId.value) = identifier;
    }
    break;
    case 1:
    {
        Byte namespaceIndex;
        UInt16 identifier;
        s >> namespaceIndex >> identifier;
        nodeId.namespaceIndex = namespaceIndex;
        emplace<UInt32>(nodeId.value) = identifier;
    }
    break;
    case 2:
    {
        s >> nodeId.namespaceIndex >> emplace<UInt32>(nodeId.value);
    }
    break;
    case 3:
    {
        s >> nodeId.namespaceIndex >> emplace<String>(nodeId.value);
    }
    break;
    case 4:
    {
        s >> nodeId.namespaceIndex >> emplace<Guid>(nodeId.value);
    }
    break;
    case 5:
    {
        s >> nodeId.namespaceIndex >> emplace<Opaque>(nodeId.value);
    }
    break;
    default:
        throw;
    }
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, NodeId const& nodeId)
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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, StatusCode& statusCode)
{
    UInt32 tmpl;
    s >> tmpl;
    statusCode = tmpl;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, StatusCode const& statusCode)
{
    UInt32 tmpl{statusCode};
    s << tmpl;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, DiagnosticInfo& diagInfo)
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

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, DiagnosticInfo const& diagInfo)
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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, QualifiedName& qn)
{
    s >> qn.namespaceIndex >> qn.name;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, QualifiedName const& qn)
{
    s << qn.namespaceIndex << qn.name;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, LocalizedText& lt)
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

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, LocalizedText const& lt)
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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, XmlElement&)
{
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, XmlElement const&)
{
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, ExpandedNodeId&)
{
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, ExpandedNodeId const&)
{
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, ExtensionObject&)
{
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, ExtensionObject const&)
{
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, DataValue& data)
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

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, DataValue const& data)
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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, Variant& variant)
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
        Int32 arrayLength;
        s >> arrayLength;
        switch (typeId)
        {
        case DataTypeId::Boolean:
        {
            s >> variant.emplace<DynamicArray<Boolean>>(arrayLength);
        }
        break;
        case DataTypeId::SByte:
        {
            s >> variant.emplace<DynamicArray<SByte>>(arrayLength);
        }
        break;
        case DataTypeId::Byte:
        {
            s >> variant.emplace<DynamicArray<Byte>>(arrayLength);
        }
        break;
        case DataTypeId::Int16:
        {
            s >> variant.emplace<DynamicArray<Int16>>(arrayLength);
        }
        break;
        case DataTypeId::UInt16:
        {
            s >> variant.emplace<DynamicArray<UInt16>>(arrayLength);
        }
        break;
        case DataTypeId::Int32:
        {
            s >> variant.emplace<DynamicArray<Int32>>(arrayLength);
        }
        break;
        case DataTypeId::UInt32:
        {
            s >> variant.emplace<DynamicArray<UInt32>>(arrayLength);
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
        case DataTypeId::Boolean:
        {
            s >> variant.emplace<Boolean>();
        }
        break;
        case DataTypeId::SByte:
        {
            s >> variant.emplace<SByte>();
        }
        break;
        case DataTypeId::Byte:
        {
            s >> variant.emplace<Byte>();
        }
        break;
        case DataTypeId::Int16:
        {
            s >> variant.emplace<Int16>();
        }
        break;
        case DataTypeId::UInt16:
        {
            s >> variant.emplace<UInt16>();
        }
        break;
        case DataTypeId::Int32:
        {
            s >> variant.emplace<Int32>();
        }
        break;
        case DataTypeId::UInt32:
        {
            s >> variant.emplace<UInt32>();
        }
        break;
        case DataTypeId::Int64:
        {
            s >> variant.emplace<Int64>();
        }
        break;
        case DataTypeId::UInt64:
        {
            s >> variant.emplace<UInt64>();
        }
        break;
        case DataTypeId::Float:
        {
            s >> variant.emplace<Float>();
        }
        break;
        case DataTypeId::Double:
        {
            s >> variant.emplace<Double>();
        }
        break;
        case DataTypeId::String:
        {
            s >> variant.emplace<String>();
        }
        break;
        case DataTypeId::DateTime:
        {
            s >> variant.emplace<DateTime>();
        }
        break;
        case DataTypeId::Guid:
        {
            s >> variant.emplace<Guid>();
        }
        break;
        case DataTypeId::ByteString:
        {
            s >> variant.emplace<ByteString>();
        }
        break;
        case DataTypeId::XmlElement:
        {
            s >> variant.emplace<XmlElement>();
        }
        break;
        case DataTypeId::NodeId:
        {
            s >> variant.emplace<NodeId>();
        }
        break;
        case DataTypeId::ExpandedNodeId:
        {
            s >> variant.emplace<ExpandedNodeId>();
        }
        break;
        case DataTypeId::StatusCode:
        {
            s >> variant.emplace<StatusCode>();
        }
        break;
        case DataTypeId::QualifiedName:
        {
            s >> variant.emplace<QualifiedName>();
        }
        break;
        case DataTypeId::LocalizedText:
        {
            s >> variant.emplace<LocalizedText>();
        }
        break;
        case DataTypeId::ExtensionObject:
        {
            s >> variant.emplace<ExtensionObject>();
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

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, Variant const& variant)
{
    Byte encodingMask{variant.encodingMask()};
    s << encodingMask;
    if (0 == encodingMask)
    {
        return s;
    }
    std::visit([&s, &encodingMask](auto&& arg)
    {
        if (encodingMask & 0x80)
        {
            Int32 arrayLength{arg.size()};
            s << arrayLength;
        }
        s << arg;
    }, *variant.value);
    return s;
}

} // namespace ua
