#pragma once

#include <memory>

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "TimerInterface.hpp"
#include "ControlLink.hpp"

namespace app
{

struct ControllerStartReq;
struct ControllerStopReq;
struct ConnectorInitRsp;
struct DetectorInitRsp;
struct ModbusInitRsp;

class Controller : public reactor::ComponentBase<CompIds::controller>
{
public:
    explicit Controller(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(ControllerStartReq const&);
    void receive(ControllerStopReq const&);
    void receive(ConnectorInitRsp const&);
    void receive(DetectorInitRsp const&);
    void receive(ModbusInitRsp const&);

private:
    void registerComponent();
};

} // namespace app
