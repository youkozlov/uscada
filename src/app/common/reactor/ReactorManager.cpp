#include "ReactorManager.hpp"

#include <iostream>
#include <chrono>
#include <thread>

#include "MsgInterface.hpp"
#include "MsgMemPool.hpp"
#include "ReactorInterface.hpp"
#include "ComponentInterface.hpp"


namespace reactor
{

ReactorManager::ReactorManager()
{
    msgMemPool = std::make_unique<MsgMemPool>(1 << 16, 128);
}

ReactorManager::~ReactorManager()
{
}

MsgMemPool& ReactorManager::getMsgMemPool()
{
    return *msgMemPool;
}

void ReactorManager::send(MsgInterface const& msg)
{
    auto& comp = components[msg.getCompId()];
    if (nullptr == comp)
    {
        std::cout << "Can not find component, compId: " << msg.getCompId() << std::endl;
        return;
    }
    comp->getReactor().send(msg);
}

void ReactorManager::addComponent(std::unique_ptr<ComponentInterface> comp)
{
    auto& stored = components[comp->getCompId()];
    if (stored)
    {
        std::cout << "Can not add component, because already exists, compId: " << comp->getCompId() << std::endl;
        return;
    }
    stored = std::move(comp);
}

void ReactorManager::addReactor(std::unique_ptr<ReactorInterface> reactor)
{
    reactors.push_back(std::move(reactor));
}

void ReactorManager::start()
{
    for (auto& reactor : reactors)
    {
        reactor->start();
    }
}

void ReactorManager::stop()
{
    for (auto& reactor : reactors)
    {
        reactor->stop();
    }
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);
}


} // namespace reactor
