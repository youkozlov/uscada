#include "Detector.hpp"

#include <iostream>

#include "MsgDetectorInitReq.hpp"
#include "MsgDetectorInitRsp.hpp"

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
          MsgDetectorInitReq::msgId()
        , [this](reactor::MsgInterface const& msg){ receive(static_cast<MsgDetectorInitReq const&>(msg)); }
    );
}

void Detector::receive(MsgDetectorInitReq const&)
{
    MsgDetectorInitRsp rsp;
    getSender().send(rsp);
}

} // namespace app
