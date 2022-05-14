#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaSecureChannelConfigRsp : public reactor::MsgBase<MsgUaSecureChannelConfigRsp, CompIds::compUaSecChannel, MsgIds::uaSecureChannelConfigRsp>
{
};

} // namespace app
