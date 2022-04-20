#pragma once

#include <memory>

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "TimerInterface.hpp"

namespace app
{

struct ControllerStartReq;
struct ControllerStopReq;
struct ConnectorInitRsp;
struct DetectorInitRsp;
struct ModbusInitRsp;
struct ModbusReleaseRsp;
struct ModbusAduReq;

class Controller : public reactor::ComponentBase<CompIds::controller>
{
public:
    explicit Controller(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(ControllerStartReq const&);
    void receive(ControllerStopReq const&);
    void receive(ConnectorInitRsp const&);
    void receive(DetectorInitRsp const&);
    void receive(ModbusInitRsp const&);
    void receive(ModbusReleaseRsp const&);
    void receive(ModbusAduReq const&);

private:
    void registerComponent();
};

} // namespace app
