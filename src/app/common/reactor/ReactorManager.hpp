#pragma once

#include <vector>
#include <map>
#include <memory>

#include "ComponentId.hpp"
#include "SenderInterface.hpp"

namespace app::reactor
{

class ReactorInterface;
class ComponentInterface;

class ReactorManager : public SenderInterface
{
public:
    ReactorManager();

    ~ReactorManager();

    void send(MsgInterface const&) final;

    void addComponent(std::unique_ptr<ComponentInterface>);

    void addReactor(std::unique_ptr<ReactorInterface>);

    void start();

    void stop();

private:
    std::vector<std::unique_ptr<ReactorInterface>> reactors;
    std::map<ComponentId, std::unique_ptr<ComponentInterface>> components;
};

} // namespace app::reactor
