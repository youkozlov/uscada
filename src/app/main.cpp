#include <iostream>
#include <chrono>
#include <thread>

#include "Deployer.hpp"
#include "ReactorManager.hpp"
#include "ControllerStartReq.hpp"
#include "ControllerStopReq.hpp"

int main(int, char**)
{
    try
    {
        reactor::ReactorManager reactorManager;

        app::Deployer deployer;

        deployer.apply(reactorManager, app::DeploymentType::cpu3);

        reactorManager.start();

        app::ControllerStartReq start;
        reactorManager.send(start);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20s);

        app::ControllerStopReq stop;
        reactorManager.send(stop);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3s);

        reactorManager.stop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}