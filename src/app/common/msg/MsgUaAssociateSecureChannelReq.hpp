#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "UaConnectionId.hpp"
#include "UaSecureChannelId.hpp"
#include "UaSessionId.hpp"

namespace app
{

struct MsgUaAssociateSecureChannelReq : public reactor::MsgBase<MsgUaAssociateSecureChannelReq, CompIds::compUaSecChannel, MsgIds::uaAssociateSecureChannelReq>
{
    UaConnectionId      connectionId;
    UaSecureChannelId   secureChannelId;
    UaSessionId         sessionId;
};

} // namespace app
