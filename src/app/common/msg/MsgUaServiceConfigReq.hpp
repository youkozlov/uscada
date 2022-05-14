#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaServiceConfigReq : public reactor::MsgBase<MsgUaServiceConfigReq, CompIds::compUaService, MsgIds::uaServiceConfigReq>
{
};

} // namespace app
