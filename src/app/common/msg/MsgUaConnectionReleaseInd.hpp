#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "UaConnectionId.hpp"

namespace app
{

struct MsgUaConnectionReleaseInd : public reactor::MsgBase<MsgUaConnectionReleaseInd, CompIds::compUaSecChannel, MsgIds::uaConnectionReleaseInd>
{
    UaConnectionId    connectionId;
    UaSecureChannelId secureChannelId;
};

} // namespace app
