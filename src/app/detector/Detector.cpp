#include "Detector.hpp"

#include <iostream>

#include "DetectorInitReq.hpp"
#include "DetectorInitRsp.hpp"

namespace app
{

Detector::Detector(reactor::SenderInterface& sender, reactor::ReactorInterface& receiver)
    : ComponentBase(sender, receiver)
{
    registerComponent();
}

void Detector::registerComponent()
{
    getReactor().registerHandler(
          DetectorInitReq::msgId
        , [this](reactor::MsgInterface const& msg){ receive(static_cast<DetectorInitReq const&>(msg)); }
    );
}

void Detector::receive(DetectorInitReq const&)
{
    std::cout << "DetectorInitReq received" << std::endl;

    DetectorInitRsp rsp;
    getSender().send(rsp);
}

} // namespace app
