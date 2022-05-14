#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaSecureChannelConfigReq : public reactor::MsgBase<MsgUaSecureChannelConfigReq, CompIds::compUaSecChannel, MsgIds::uaSecureChannelConfigReq>
{
};

} // namespace app
