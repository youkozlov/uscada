#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgDetectorInitReq : public reactor::MsgBase<MsgDetectorInitReq, CompIds::compDetector, MsgIds::detectorInitReq>
{
};

} // namespace app
