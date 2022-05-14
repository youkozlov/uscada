#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaSecureChannelInitReq : public reactor::MsgBase<MsgUaSecureChannelInitReq, CompIds::compUaSecChannel, MsgIds::uaSecureChannelInitReq>
{
};

} // namespace app
