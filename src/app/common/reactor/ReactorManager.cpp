#include "ReactorManager.hpp"

#include <iostream>
#include <chrono>
#include <thread>

#include "MsgInterface.hpp"
#include "ReactorInterface.hpp"
#include "ComponentInterface.hpp"
#include "MaxMsgSize.hpp"
#include "Logger.hpp"

namespace reactor
{

ReactorManager::ReactorManager()
{}

ReactorManager::~ReactorManager()
{
}

void ReactorManager::send(MsgInterface const& msg)
{
    auto& comp = components[msg.getCompId()];
    if (nullptr == comp)
    {
        LM(GEN, LE, "Can not find component, compId=%zu", msg.getCompId());
        return;
    }
    comp->getReactor().send(msg);
}

void ReactorManager::addComponent(std::unique_ptr<ComponentInterface> comp)
{
    auto& stored = components[comp->getCompId()];
    if (stored)
    {
        LM(GEN, LE, "Can not add component, because already exists, compId=%zu", comp->getCompId());
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
