#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaServiceInitReq : public reactor::MsgBase<MsgUaServiceInitReq, CompIds::compUaService, MsgIds::uaServiceInitReq>
{
};

} // namespace app
