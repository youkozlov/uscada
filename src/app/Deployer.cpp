#include "Deployer.hpp"

#include <map>

#include "CompDefs.hpp"
#include "Container.hpp"
#include "ReactorSimple.hpp"
#include "ConnectorSimple.hpp"
#include "Modbus.hpp"
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
                {{CompIds::connector, CompIds::detector, CompIds::controller}, 1, 0}
            };
    case DeploymentType::cpu3:
        return
            {
                  {{CompIds::connector}, 1,  0b00010}
                , {{CompIds::modbus}, 1,     0b00100}
                , {{CompIds::controller}, 1, 0b01000}
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
        reactor::ReactorSimple::Init reactorInit
        {
              container.numThreads
            , container.cpuMask
            , manager.getMsgMemPool()
        };
        std::unique_ptr<reactor::ReactorInterface> reactor{new reactor::ReactorSimple(reactorInit)};
        for (auto& compId : container.components)
        {
            switch (compId)
            {
            case CompIds::connector:
            {
                std::unique_ptr<reactor::ComponentInterface> comp{new ConnectorSimple(manager, *reactor)};
                manager.addComponent(std::move(comp));
            }
            break;
            case CompIds::modbus:
            {
                std::unique_ptr<reactor::ComponentInterface> comp{new Modbus(manager, *reactor)};
                manager.addComponent(std::move(comp));
            }
            break;
            case CompIds::controller:
            {
                std::unique_ptr<reactor::ComponentInterface> comp{new Controller(manager, *reactor)};
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
