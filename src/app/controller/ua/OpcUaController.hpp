#pragma once

#include "OpcUaServer.hpp"
#include "OpcUaClient.hpp"

namespace app::controller
{

class OpcUaController
{
public:
    explicit OpcUaController();

    ~OpcUaController();

    void start();

    void connect();

private:
    ua::OpcUaServer server;
    ua::OpcUaClient client;
};

} // namespace app::controller
