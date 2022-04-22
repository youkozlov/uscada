#pragma once

#include <memory>
#include <array>

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
struct ModbusConfigRsp;
struct ModbusClientAduRsp;
struct ModbusAduReq;
}

namespace app::controller
{

class Controller : public reactor::ComponentBase<CompIds::compController>
{
public:
    explicit Controller(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(ControllerStartReq const&);
    void receive(ControllerStopReq const&);
    void receive(ConnectorInitRsp const&);
    void receive(DetectorInitRsp const&);
    void receive(ModbusInitRsp const&);
    void receive(ModbusReleaseRsp const&);
    void receive(ModbusConfigRsp const&);
    void receive(ModbusClientAduRsp const&);
    void receive(ModbusAduReq const&);

private:
    void registerComponent();

    std::array<uint16_t, 65535> serverRegs;
    std::array<uint16_t, 65535> clientRegs;
};

} // namespace app::controller
