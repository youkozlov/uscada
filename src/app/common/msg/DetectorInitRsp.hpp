#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct DetectorInitRsp : public reactor::MsgBase<DetectorInitRsp, CompIds::controller, MsgIds::detectorInitRsp>
{
};

} // namespace app
