#include "Deployer.hpp"

#include <map>

#include "CompDefs.hpp"
#include "Container.hpp"
#include "Reactor.hpp"
#include "ConnectorSimple.hpp"
#include "ModbusComponent.hpp"
#include "ControllerComponent.hpp"
#include "ReactorManager.hpp"
#include "Logger.hpp"

namespace app
{

namespace
{
std::vector<reactor::Container> getDepl(DeploymentType depType)
{
    switch (depType)
    {
    case DeploymentType::def:
        return
            {
                {{CompIds::compConnector, CompIds::compDetector, CompIds::compController}, 1, 0}
            };
    case DeploymentType::cpu3:
        return
            {
                  {{CompIds::compConnector}, 1,  0b00000100}
                , {{CompIds::compModbus}, 1,     0b00010000}
                , {{CompIds::compController}, 1, 0b01000000}
            };
    default:
        LM(GEN, LE, "Unexpected");
        break;
    }
    return {};
}
}

void Deployer::apply(reactor::ReactorManager& manager, DeploymentType depType)
{
    unsigned id = 0;
    for (auto const& container : getDepl(depType))
    {
        reactor::Reactor::Init reactorInit
        {
              id++
            , container.numThreads
            , container.cpuMask
        };
        std::unique_ptr<reactor::ReactorInterface> reactor{new reactor::Reactor(reactorInit)};
        for (auto& compId : container.components)
        {
            switch (compId)
            {
            case CompIds::compConnector:
            {
                std::unique_ptr<reactor::ComponentInterface> comp{new ConnectorSimple(manager, *reactor)};
                manager.addComponent(std::move(comp));
            }
            break;
            case CompIds::compModbus:
            {
                std::unique_ptr<reactor::ComponentInterface> comp{new modbus::ModbusComponent(manager, *reactor)};
                manager.addComponent(std::move(comp));
            }
            break;
            case CompIds::compController:
            {
                std::unique_ptr<reactor::ComponentInterface> comp{new controller::ControllerComponent(manager, *reactor)};
                manager.addComponent(std::move(comp));
            }
            break;
            default:
                LM(GEN, LE, "Unexpected");
            break;
            }
        }
        manager.addReactor(std::move(reactor));
    }
}

} // namespace app
