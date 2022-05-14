#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgDetectorInitRsp : public reactor::MsgBase<MsgDetectorInitRsp, CompIds::compController, MsgIds::detectorInitRsp>
{
};

} // namespace app
