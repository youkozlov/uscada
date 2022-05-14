#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaSecureChannelReleaseRsp : public reactor::MsgBase<MsgUaSecureChannelReleaseRsp, CompIds::compUaSecChannel, MsgIds::uaSecureChannelReleaseRsp>
{
};

} // namespace app
