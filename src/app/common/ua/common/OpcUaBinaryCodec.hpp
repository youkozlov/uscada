#pragma once

#include "OpcUaSduBuffer.hpp"
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

#include "MessageHeader.hpp"
#include "HelloMessage.hpp"
#include "AcknowledgeMessage.hpp"
#include "ErrorMessage.hpp"
#include "ReverseHelloMessage.hpp"

#include "UaMessageHeader.hpp"
#include "UaSecurityHeader.hpp"
#include "UaSequenceHeader.hpp"
#include "UaRequestHeader.hpp"
#include "UaChannelSecurityToken.hpp"
#include "UaOpenSecureChannelReq.hpp"
#include "UaOpenSecureChannelRsp.hpp"
#include "UaCloseSecureChannelReq.hpp"
#include "UaCloseSecureChannelRsp.hpp"
#include "UaGetEndpointsReq.hpp"
#include "UaGetEndpointsRsp.hpp"
#include "UaEndpointDescription.hpp"
#include "UaCreateSessionReq.hpp"
#include "UaCreateSessionRsp.hpp"
#include "UaCloseSessionReq.hpp"
#include "UaCloseSessionRsp.hpp"
#include "UaActivateSessionReq.hpp"
#include "UaActivateSessionRsp.hpp"
#include "UaReadReq.hpp"
#include "UaReadRsp.hpp"
#include "ReadValueId.hpp"

namespace app::ua
{

class OpcUaBinaryCodec
{
public:
    explicit OpcUaBinaryCodec(OpcUaSduBuffer&);

    ~OpcUaBinaryCodec();

    void write(std::uint8_t);

    std::uint8_t read();

    OpcUaSduBuffer& buf();

    OpcUaSduBuffer const& buf() const;

private:
    OpcUaSduBuffer& buffer;
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
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, MessageHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, MessageHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, HelloMessage&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, HelloMessage const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, AcknowledgeMessage&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, AcknowledgeMessage const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, ErrorMessage&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, ErrorMessage const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, ReverseHelloMessage&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, ReverseHelloMessage const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaMessageHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaMessageHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaSecurityHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaSecurityHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaSecurityTokenHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaSecurityTokenHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaSequenceHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaSequenceHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaRequestHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaRequestHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaOpenSecureChannelReq&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaOpenSecureChannelReq const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaCloseSecureChannelReq&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaCloseSecureChannelReq const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaCloseSecureChannelRsp&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaCloseSecureChannelRsp const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaChannelSecurityToken&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaChannelSecurityToken const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaResponseHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaResponseHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaOpenSecureChannelRsp&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaOpenSecureChannelRsp const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaGetEndpointsReq&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaGetEndpointsReq const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaGetEndpointsRsp&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaGetEndpointsRsp const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaEndpointDescription&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaEndpointDescription const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaApplicationDescription&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaApplicationDescription const&);
//OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaApplicationInstanceCertificate&);
//OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaApplicationInstanceCertificate const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaUserTokenPolicy&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaUserTokenPolicy const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaCreateSessionReq&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaCreateSessionReq const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaSignatureData&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaSignatureData const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaCreateSessionRsp&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaCreateSessionRsp const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaCloseSessionReq&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaCloseSessionReq const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaCloseSessionRsp&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaCloseSessionRsp const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaActivateSessionReq&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaActivateSessionReq const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaActivateSessionRsp&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaActivateSessionRsp const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, ReadValueId&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, ReadValueId const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaReadReq&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaReadReq const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UaReadRsp&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UaReadRsp const&);

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
    Int32 arrayLength;
    s >> arrayLength;
    arr.resize(arrayLength);
    for (auto& it : arr)
    {
        s >> it;
    }
    return s;
}
template <typename T>
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, DynamicArray<T> const& arr)
{
    Int32 arrayLength{arr.size()};
    s << arrayLength;
    for (auto& it : arr)
    {
        s << it;
    }
    return s;
}
template <typename...T>
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, std::tuple<T...>& tup)
{
    std::apply([&s = s](auto&... args) {(( s >> args ), ...);}, tup);
    return s;
}
template <typename...T>
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, std::tuple<T...> const& tup)
{
    std::apply([&s = s](auto const&... args) {(( s << args ), ...);}, tup);
    return s;
}
template <typename DataType, DataTypeId Id>
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UaMsgCont<DataType, Id>& data)
{
    s >> data.eNodeId
      >> data.msg;
    return s;
}
template <typename DataType, DataTypeId Id>
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UaMsgCont<DataType, Id> const& data)
{
    s << data.eNodeId
      << data.msg;
    return s;
}
} // namespace app::ua
