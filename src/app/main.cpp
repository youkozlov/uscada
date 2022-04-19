#include <iostream>
#include <chrono>
#include <thread>

#include "Deployer.hpp"
#include "ReactorManager.hpp"
#include "ControllerStartReq.hpp"

int main(int, char**)
{
    try
    {
        reactor::ReactorManager reactorManager;

        app::Deployer deployer;

        deployer.apply(reactorManager, app::DeploymentType::cpu3);

        reactorManager.start();

        app::ControllerStartReq req;
        reactorManager.send(req);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(10000ms);

        reactorManager.stop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}