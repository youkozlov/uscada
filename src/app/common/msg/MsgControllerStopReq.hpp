#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgControllerStopReq : public reactor::MsgBase<MsgControllerStopReq, CompIds::compController, MsgIds::controllerStopReq>
{
};

} // namespace app
