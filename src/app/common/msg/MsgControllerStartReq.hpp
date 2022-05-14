#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgControllerStartReq : public reactor::MsgBase<MsgControllerStartReq, CompIds::compController, MsgIds::controllerStartReq>
{
};

} // namespace app
