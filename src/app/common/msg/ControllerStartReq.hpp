#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ControllerStartReq : public reactor::MsgBase<ControllerStartReq, CompIds::controller, MsgIds::controllerStartReq>
{
};

} // namespace app
