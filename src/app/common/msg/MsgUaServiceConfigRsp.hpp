#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaServiceConfigRsp : public reactor::MsgBase<MsgUaServiceConfigRsp, CompIds::compUaSecChannel, MsgIds::uaServiceConfigRsp>
{
};

} // namespace app
