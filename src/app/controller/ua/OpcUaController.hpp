#pragma once

#include "ServerConnection.hpp"
#include "ClientConnection.hpp"

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
};

} // namespace app::controller
