#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaSecureChannelInitRsp : public reactor::MsgBase<MsgUaSecureChannelInitRsp, CompIds::compUaSecChannel, MsgIds::uaSecureChannelInitRsp>
{
};

} // namespace app
