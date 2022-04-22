#include "Deployer.hpp"

#include <map>

#include "CompDefs.hpp"
#include "Container.hpp"
#include "Reactor.hpp"
#include "ConnectorSimple.hpp"
#include "ModbusComponent.hpp"
#include "Controller.hpp"
#include "ReactorManager.hpp"

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
                  {{CompIds::compConnector}, 1,  0b00010}
                , {{CompIds::compModbus}, 1,     0b00100}
                , {{CompIds::compController}, 1, 0b01000}
            };
    default:
        break;
    }
    return {};
}
}

void Deployer::apply(reactor::ReactorManager& manager, DeploymentType depType)
{
    for (auto const& container : getDepl(depType))
    {
        reactor::Reactor::Init reactorInit
        {
              container.numThreads
            , container.cpuMask
            , manager.getMsgMemPool()
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
                std::unique_ptr<reactor::ComponentInterface> comp{new controller::Controller(manager, *reactor)};
                manager.addComponent(std::move(comp));
            }
            break;
            default:
            break;
            }
        }
        manager.addReactor(std::move(reactor));
    }
}

} // namespace app
