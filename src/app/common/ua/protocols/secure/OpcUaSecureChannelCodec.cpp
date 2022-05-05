#include "OpcUaSecureChannelCodec.hpp"

namespace app::ua
{

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UascMessageHeader& val)
{
    s   >> val.messageType
        >> val.isFinal
        >> val.messageSize
        >> val.secureChannelId;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UascMessageHeader const& val)
{
    s   << val.messageType
        << val.isFinal
        << val.messageSize
        << val.secureChannelId;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UascSecurityHeader& val)
{
    s   >> val.tokenId;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UascSecurityHeader const& val)
{
    s   << val.tokenId;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UascSequenceHeader& val)
{
    s   >> val.sequenceNumber
        >> val.requestId;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UascSequenceHeader const& val)
{
    s   << val.sequenceNumber
        << val.requestId;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UascRequestHeader& val)
{
    s   >> val.authentificationToken
        >> val.timestamp
        >> val.requestHandle
        >> val.returnDignostics
        >> val.auditEntityId
        >> val.timeoutHint
        >> val.isOnline;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UascRequestHeader const& val)
{
    s   << val.authentificationToken
        << val.timestamp
        << val.requestHandle
        << val.returnDignostics
        << val.auditEntityId
        << val.timeoutHint
        << val.isOnline;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UascOpenSecureChannelReq& val)
{
    s   >> val.requestHdr
        >> val.clientProtocolVer
        >> val.securityTokenRequestType
        >> val.securityMode
        >> val.clientNonce
        >> val.requestLifetime;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UascOpenSecureChannelReq const& val)
{
    s   << val.requestHdr
        << val.clientProtocolVer
        << val.securityTokenRequestType
        << val.securityMode
        << val.clientNonce
        << val.requestLifetime;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UascChannelSecurityToken& val)
{
    s   >> val.secureChannelId
        >> val.tokenId
        >> val.createdAt
        >> val.revisedLifetime;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UascChannelSecurityToken const& val)
{
    s   << val.secureChannelId
        << val.tokenId
        << val.createdAt
        << val.revisedLifetime;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UascResponseHeader& val)
{
    s   >> val.timestamp
        >> val.requestHandle
        >> val.serviceResult
        >> val.serviceDiagnostics
        >> val.stringTable;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UascResponseHeader const& val)
{
    s   << val.timestamp
        << val.requestHandle
        << val.serviceResult
        << val.serviceDiagnostics
        << val.stringTable;
    return s;
}

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec& s, UascOpenSecureChannelRsp& val)
{
    s   >> val.responseHdr
        >> val.serverProtocolVer
        >> val.securityToken
        >> val.serverNonce;
    return s;
}

OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec& s, UascOpenSecureChannelRsp const& val)
{
    s   << val.responseHdr
        << val.serverProtocolVer
        << val.securityToken
        << val.serverNonce;
    return s;
}

} // namespace app::ua
