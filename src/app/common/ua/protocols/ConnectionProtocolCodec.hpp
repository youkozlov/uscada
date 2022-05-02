#pragma once

#include "OpcUaBinaryCodec.hpp"

#include "MessageHeader.hpp"
#include "HelloMessage.hpp"
#include "AcknowledgeMessage.hpp"
#include "ErrorMessage.hpp"
#include "ReverseHelloMessage.hpp"

namespace ua
{

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

} // namespace ua
