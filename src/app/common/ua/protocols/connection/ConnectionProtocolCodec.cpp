#include "ConnectionProtocolCodec.hpp"

namespace app::ua
{

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

} // namespace app::ua
