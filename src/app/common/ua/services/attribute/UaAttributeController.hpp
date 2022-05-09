#pragma once

#include "UaReadReq.hpp"
#include "UaServiceHandler.hpp"

namespace app::ua
{

class UaAttributeController
{
public:
    UaAttributeController();
    ~UaAttributeController();

    void receive(UaReadReq const&, UaServiceHandler);

private:
};

} // namespace app::ua
