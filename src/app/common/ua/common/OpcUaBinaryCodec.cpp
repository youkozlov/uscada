#include "OpcUaBinaryCodec.hpp"
#include "Logger.hpp"

#include <cstring>

namespace app::ua
{

OpcUaBinaryCodec::OpcUaBinaryCodec(OpcUaSduBuffer& b)
    : buffer(b)
{
}

OpcUaBinaryCodec::~OpcUaBinaryCodec()
{
}

void OpcUaBinaryCodec::write(std::uint8_t val)
{
    buffer.write(val);
}

std::uint8_t OpcUaBinaryCodec::read()
{
    return buffer.read();
}

OpcUaSduBuffer& OpcUaBinaryCodec::buf()
{
    return buffer;
}

OpcUaSduBuffer const& OpcUaBinaryCodec::buf() const
{
    return buffer;
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
    switch (encByte & 0xF)
    {
    case 0:
    {
        LM(GEN, LD, "NodeId 2 bytes");

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

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, ExpandedNodeId& data)
{
    uint8_t const& encodingMask = *s.buf().begin();
    s >> data.nodeId;
    if (encodingMask & 0x80)
    {
        s >> data.namespaceUri;
    }
    if (encodingMask & 0x40)
    {
        s >> data.serverIndex;
    }
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, ExpandedNodeId const& data)
{
    uint8_t& encodingMask = *s.buf().begin();
    s << data.nodeId;
    if (data.encodingMask() & 0x1)
    {
        encodingMask |= 0x80;
        s << data.namespaceUri;
    }
    if (data.encodingMask() & 0x2)
    {
        encodingMask |= 0x40;
        s << data.serverIndex;
    }
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, ExtensionObject& data)
{
    Byte encodingMask;
    s >> data.nodeId >> encodingMask;
    switch (encodingMask)
    {
    case 0:
    break;
    case 1:
        s >> data.byteString;
    break;
    case 2:
        s >> data.byteString;
    break;
    default:
        LM(GEN, LE, "Unexpected, %u", (int)encodingMask);
        break;
    }
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, ExtensionObject const& data)
{
    Byte encodingMask{data.encodingMask()};
    s << data.nodeId << encodingMask;
    switch (encodingMask)
    {
    case 0:
    break;
    case 1:
        s << data.byteString;
    break;
    case 2:
        s << data.byteString;
    break;
    default:
        LM(GEN, LE, "Unexpected");
        break;
    }
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
        switch (typeId)
        {
        case DataTypeId::Boolean:
        {
            s >> variant.emplace<DynamicArray<Boolean>>();
        }
        break;
        case DataTypeId::SByte:
        {
            s >> variant.emplace<DynamicArray<SByte>>();
        }
        break;
        case DataTypeId::Byte:
        {
            s >> variant.emplace<DynamicArray<Byte>>();
        }
        break;
        case DataTypeId::Int16:
        {
            s >> variant.emplace<DynamicArray<Int16>>();
        }
        break;
        case DataTypeId::UInt16:
        {
            s >> variant.emplace<DynamicArray<UInt16>>();
        }
        break;
        case DataTypeId::Int32:
        {
            s >> variant.emplace<DynamicArray<Int32>>();
        }
        break;
        case DataTypeId::UInt32:
        {
            s >> variant.emplace<DynamicArray<UInt32>>();
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
        s << arg;
    }, *variant.value);
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, MessageHeader& val)
{
    s   >> val.messageType
        >> val.isFinal
        >> val.messageSize;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, MessageHeader const& val)
{
    s   << val.messageType
        << val.isFinal
        << val.messageSize;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, HelloMessage& val)
{
    s   >> val.protocolVersion
        >> val.receiveBufferSize 
        >> val.sendBufferSize
        >> val.maxMessageSize
        >> val.maxChunkCount
        >> val.endpointUrl;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, HelloMessage const& val)
{
    s   << val.protocolVersion
        << val.receiveBufferSize 
        << val.sendBufferSize
        << val.maxMessageSize
        << val.maxChunkCount
        << val.endpointUrl;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, AcknowledgeMessage& val)
{
    s   >> val.protocolVersion
        >> val.receiveBufferSize 
        >> val.sendBufferSize
        >> val.maxMessageSize
        >> val.maxChunkCount;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, AcknowledgeMessage const& val)
{
    s   << val.protocolVersion
        << val.receiveBufferSize 
        << val.sendBufferSize
        << val.maxMessageSize
        << val.maxChunkCount;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, ErrorMessage& val)
{
    s   >> val.error
        >> val.reason;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, ErrorMessage const& val)
{
    s   << val.error
        << val.reason;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, ReverseHelloMessage& val)
{
    s   >> val.serverUri
        >> val.endpointUrl;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, ReverseHelloMessage const& val)
{
    s   << val.serverUri
        << val.endpointUrl;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaMessageHeader& val)
{
    LM(UA, LD, "UaMessageHeader>>");

    s   >> val.messageType
        >> val.isFinal
        >> val.messageSize
        >> val.secureChannelId;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaMessageHeader const& val)
{
    LM(UA, LD, "UaMessageHeader<<");

    s   << val.messageType
        << val.isFinal
        << val.messageSize
        << val.secureChannelId;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaSecurityHeader& val)
{
    LM(UA, LD, "UaSecurityHeader>>");

    s   >> val.securityPolicyUri
        >> val.senderCertificate
        >> val.receiverCertificateThumbprint;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaSecurityHeader const& val)
{
    LM(UA, LD, "UaSecurityHeader<<");

    s   << val.securityPolicyUri
        << val.senderCertificate
        << val.receiverCertificateThumbprint;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaSecurityTokenHeader& val)
{
    LM(UA, LD, "UaSecurityTokenHeader>>");

    s   >> val.tokenId;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaSecurityTokenHeader const& val)
{
    LM(UA, LD, "UaSecurityTokenHeader<<");

    s   << val.tokenId;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaSequenceHeader& val)
{
    LM(UA, LD, "UaSequenceHeader>>");

    s   >> val.sequenceNumber
        >> val.requestId;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaSequenceHeader const& val)
{
    LM(UA, LD, "UaSequenceHeader<<");

    s   << val.sequenceNumber
        << val.requestId;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaRequestHeader& val)
{
    LM(UA, LD, "UaRequestHeader>>");

    s   >> val.authentificationToken
        >> val.timestamp
        >> val.requestHandle
        >> val.returnDignostics
        >> val.auditEntityId
        >> val.timeoutHint
        >> val.additionalHeader;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaRequestHeader const& val)
{
    LM(UA, LD, "UaRequestHeader<<");

    s   << val.authentificationToken
        << val.timestamp
        << val.requestHandle
        << val.returnDignostics
        << val.auditEntityId
        << val.timeoutHint
        << val.additionalHeader;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaOpenSecureChannelReq& val)
{
    LM(UA, LD, "UaOpenSecureChannelReq>>");

    s   >> val.requestHdr
        >> val.clientProtocolVer
        >> val.securityTokenRequestType
        >> val.securityMode
        >> val.clientNonce
        >> val.requestLifetime;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaOpenSecureChannelReq const& val)
{
    LM(UA, LD, "UaOpenSecureChannelReq<<");

    s   << val.requestHdr
        << val.clientProtocolVer
        << val.securityTokenRequestType
        << val.securityMode
        << val.clientNonce
        << val.requestLifetime;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaCloseSecureChannelReq& val)
{
    LM(UA, LD, "UaCloseSecureChannelReq>>");

    s   >> val.requestHdr;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaCloseSecureChannelReq const& val)
{
    LM(UA, LD, "UaCloseSecureChannelReq<<");

    s   << val.requestHdr;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaCloseSecureChannelRsp& val)
{
    LM(UA, LD, "UaCloseSecureChannelRsp>>");

    s   >> val.responseHdr;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaCloseSecureChannelRsp const& val)
{
    LM(UA, LD, "UaCloseSecureChannelRsp<<");

    s   << val.responseHdr;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaChannelSecurityToken& val)
{
    LM(UA, LD, "UaChannelSecurityToken>>");

    s   >> val.secureChannelId
        >> val.tokenId
        >> val.createdAt
        >> val.revisedLifetime;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaChannelSecurityToken const& val)
{
    LM(UA, LD, "UaChannelSecurityToken<<");

    s   << val.secureChannelId
        << val.tokenId
        << val.createdAt
        << val.revisedLifetime;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaResponseHeader& val)
{
    LM(UA, LD, "UaResponseHeader>>");

    s   >> val.timestamp
        >> val.requestHandle
        >> val.serviceResult
        >> val.serviceDiagnostics
        >> val.stringTable
        >> val.additionalHeader;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaResponseHeader const& val)
{
    LM(UA, LD, "UaResponseHeader<<");

    s   << val.timestamp
        << val.requestHandle
        << val.serviceResult
        << val.serviceDiagnostics
        << val.stringTable
        << val.additionalHeader;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaOpenSecureChannelRsp& val)
{
    LM(UA, LD, "UaOpenSecureChannelRsp>>");

    s   >> val.responseHdr
        >> val.serverProtocolVer
        >> val.securityToken
        >> val.serverNonce;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaOpenSecureChannelRsp const& val)
{
    LM(UA, LD, "UaOpenSecureChannelRsp<<");

    s   << val.responseHdr
        << val.serverProtocolVer
        << val.securityToken
        << val.serverNonce;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaGetEndpointsReq& val)
{
    LM(UA, LD, "UaGetEndpointsReq>>");
    s   >> val.requestHdr
        >> val.endpointUrl
        >> val.localeIds
        >> val.profileUris;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaGetEndpointsReq const& val)
{
    LM(UA, LD, "UaGetEndpointsReq<<");
    s   << val.requestHdr
        << val.endpointUrl
        << val.localeIds
        << val.profileUris;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaGetEndpointsRsp& val)
{
    LM(UA, LD, "UaGetEndpointsRsp>>");
    s   >> val.responseHdr
        >> val.endpointDescription;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaGetEndpointsRsp const& val)
{
    LM(UA, LD, "UaGetEndpointsRsp<<");
    s   << val.responseHdr
        << val.endpointDescription;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaEndpointDescription& val)
{
    LM(UA, LD, "UaEndpointDescription>>");
    s   >> val.endpointUrl
        >> val.server
        >> val.serverCertificate
        >> val.securityMode
        >> val.securityPolicyUri
        >> val.userIdentityTokens
        >> val.transportProfileUri
        >> val.securityLevel;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaEndpointDescription const& val)
{
    LM(UA, LD, "UaEndpointDescription<<");
    s   << val.endpointUrl
        << val.server
        << val.serverCertificate
        << val.securityMode
        << val.securityPolicyUri
        << val.userIdentityTokens
        << val.transportProfileUri
        << val.securityLevel;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaApplicationDescription& val)
{
    LM(UA, LD, "UaApplicationDescription>>");
    s   >> val.applicationUri
        >> val.productUri
        >> val.applicationName
        >> val.applicationType
        >> val.gatewayServerUri
        >> val.discoveryProfileUri
        >> val.discoveryUrls;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaApplicationDescription const& val)
{
    LM(UA, LD, "UaApplicationDescription<<");
    s   << val.applicationUri
        << val.productUri
        << val.applicationName
        << val.applicationType
        << val.gatewayServerUri
        << val.discoveryProfileUri
        << val.discoveryUrls;
    return s;
}

/*
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaApplicationInstanceCertificate& val)
{
    LM(UA, LD, "UaApplicationInstanceCertificate>>");
    s   >> val.version
        >> val.serialNumber
        >> val.signatureAlgorithm
        >> val.signature
        >> val.issuer
        >> val.validFrom
        >> val.validTo
        >> val.subject
        >> val.applicationUri
        >> val.hostnames
        >> val.publicKey
        >> val.keyUsage;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaApplicationInstanceCertificate const& val)
{
    LM(UA, LD, "UaApplicationInstanceCertificate<<");
    s   << val.version
        << val.serialNumber
        << val.signatureAlgorithm
        << val.signature
        << val.issuer
        << val.validFrom
        << val.validTo
        << val.subject
        << val.applicationUri
        << val.hostnames
        << val.publicKey
        << val.keyUsage;
    return s;
}
*/

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaUserTokenPolicy& val)
{
    LM(UA, LD, "UaUserTokenPolicy>>");
    s   >> val.policyId
        >> val.tokenType
        >> val.issuedTokenType
        >> val.issuerEndpointUrl
        >> val.securityPolicyUri;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaUserTokenPolicy const& val)
{
    LM(UA, LD, "UaUserTokenPolicy<<");
    s   << val.policyId
        << val.tokenType
        << val.issuedTokenType
        << val.issuerEndpointUrl
        << val.securityPolicyUri;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaCreateSessionReq& val)
{
    LM(UA, LD, "UaCreateSessionReq>>");
    s   >> val.requestHdr
        >> val.clientDescription
        >> val.serverUri
        >> val.endpointUrl
        >> val.sessionName
        >> val.clientNonce
        >> val.clientCertificate
        >> val.requestedSessionTimeout
        >> val.maxResponseMessageSize;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaCreateSessionReq const& val)
{
    LM(UA, LD, "UaCreateSessionReq<<");
    s   << val.requestHdr
        << val.clientDescription
        << val.serverUri
        << val.endpointUrl
        << val.sessionName
        << val.clientNonce
        << val.clientCertificate
        << val.requestedSessionTimeout
        << val.maxResponseMessageSize;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaSignatureData& val)
{
    LM(UA, LD, "UaSignatureData>>");
    s   >> val.algorithm
        >> val.signature;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaSignatureData const& val)
{
    LM(UA, LD, "UaSignatureData<<");
    s   << val.algorithm
        << val.signature;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaCreateSessionRsp& val)
{
    LM(UA, LD, "UaCreateSessionRsp>>");
    s   >> val.responseHdr
        >> val.sessionId
        >> val.authenticationToken
        >> val.revisedSessionTimeout
        >> val.serverNonce
        >> val.serverCertificate
        >> val.serverEndpoints
        >> val.signedSoftwareCertificate
        >> val.serverSignature
        >> val.maxRequestMessageSize;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaCreateSessionRsp const& val)
{
    LM(UA, LD, "UaCreateSessionRsp<<");
    s   << val.responseHdr
        << val.sessionId
        << val.authenticationToken
        << val.revisedSessionTimeout
        << val.serverNonce
        << val.serverCertificate
        << val.serverEndpoints
        << val.signedSoftwareCertificate
        << val.serverSignature
        << val.maxRequestMessageSize;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaCloseSessionReq& val)
{
    LM(UA, LD, "UaCloseSessionReq>>");
    s   >> val.requestHdr
        >> val.deleteSubscriptions;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaCloseSessionReq const& val)
{
    LM(UA, LD, "UaCloseSessionReq<<");
    s   << val.requestHdr
        << val.deleteSubscriptions;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaCloseSessionRsp& val)
{
    LM(UA, LD, "UaCloseSessionRsp>>");
    s   >> val.responseHdr;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaCloseSessionRsp const& val)
{
    LM(UA, LD, "UaCloseSessionRsp<<");
    s   << val.responseHdr;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaActivateSessionReq& val)
{
    LM(UA, LD, "UaActivateSessionReq>>");
    s   >> val.requestHdr
        >> val.clientSignature
        >> val.clientSoftwareCertificates
        >> val.localeIds
        >> val.userIdentityToken
        >> val.userTokenSignature;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaActivateSessionReq const& val)
{
    LM(UA, LD, "UaActivateSessionReq<<");
    s   << val.requestHdr
        << val.clientSignature
        << val.clientSoftwareCertificates
        << val.localeIds
        << val.userIdentityToken
        << val.userTokenSignature;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaActivateSessionRsp& val)
{
    LM(UA, LD, "UaActivateSessionRsp>>");
    s   >> val.responseHdr
        >> val.serverNonce
        >> val.results
        >> val.diagnosticInfos;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaActivateSessionRsp const& val)
{
    LM(UA, LD, "UaActivateSessionRsp<<");
    s   << val.responseHdr
        << val.serverNonce
        << val.results
        << val.diagnosticInfos;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, ReadValueId& val)
{
    LM(UA, LD, "ReadeValueId>>");
    s   >> val.nodeId
        >> val.attributeId
        >> val.indexRange
        >> val.dataEncoding;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, ReadValueId const& val)
{
    LM(UA, LD, "ReadeValueId<<");
    s   << val.nodeId
        << val.attributeId
        << val.indexRange
        << val.dataEncoding;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaReadReq& val)
{
    LM(UA, LD, "UaReadReq>>");
    s   >> val.requestHdr
        >> val.maxAge
        >> val.timestampsToReturn
        >> val.nodesToRead;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaReadReq const& val)
{
    LM(UA, LD, "UaReadReq<<");
    s   << val.requestHdr
        << val.maxAge
        << val.timestampsToReturn
        << val.nodesToRead;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaReadRsp& val)
{
    LM(UA, LD, "UaReadRsp>>");
    s   >> val.responseHdr
        >> val.results
        >> val.diagnosticInfos;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaReadRsp const& val)
{
    LM(UA, LD, "UaReadRsp<<");
    s   << val.responseHdr
        << val.results
        << val.diagnosticInfos;
    return s;
}


} // namespace app::ua
