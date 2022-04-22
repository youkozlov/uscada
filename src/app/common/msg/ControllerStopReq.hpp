#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ControllerStopReq : public reactor::MsgBase<ControllerStopReq, CompIds::compController, MsgIds::controllerStopReq>
{
};

} // namespace app
