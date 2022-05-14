#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "MsgDetectorInitReq.hpp"

namespace app
{

class Detector : public reactor::ComponentBase<CompIds::compDetector>
{
public:
    explicit Detector(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(MsgDetectorInitReq const&);

private:
    void registerComponent();
};

} // namespace app
