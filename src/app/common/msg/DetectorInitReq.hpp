#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct DetectorInitReq : public reactor::MsgBase<DetectorInitReq, CompIds::compDetector, MsgIds::detectorInitReq>
{
};

} // namespace app
