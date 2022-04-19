#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"

namespace app
{

struct DetectorInitReq;

class Detector : public reactor::ComponentBase<CompIds::detector>
{
public:
    explicit Detector(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(DetectorInitReq const&);

private:
    void registerComponent();
};

} // namespace app
