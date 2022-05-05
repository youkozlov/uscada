#pragma once

#include "OpcUaBinaryCodec.hpp"

#include "UascMessageHeader.hpp"
#include "UascSecurityHeader.hpp"
#include "UascSequenceHeader.hpp"
#include "UascRequestHeader.hpp"
#include "UascChannelSecurityToken.hpp"
#include "UascOpenSecureChannelReq.hpp"
#include "UascOpenSecureChannelRsp.hpp"

namespace app::ua
{

OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UascMessageHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UascMessageHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UascSecurityHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UascSecurityHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UascSequenceHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UascSequenceHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UascRequestHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UascRequestHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UascOpenSecureChannelReq&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UascOpenSecureChannelReq const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UascChannelSecurityToken&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UascChannelSecurityToken const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UascResponseHeader&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UascResponseHeader const&);
OpcUaBinaryCodec& operator>>(OpcUaBinaryCodec&, UascOpenSecureChannelRsp&);
OpcUaBinaryCodec& operator<<(OpcUaBinaryCodec&, UascOpenSecureChannelRsp const&);

} // namespace app::ua
