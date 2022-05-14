#pragma once

#include <map>
#include "DataType.hpp"
#include "UaServiceInterface.hpp"

#include "UaDiscoveryService.hpp"
#include "UaSessionService.hpp"
#include "UaAttributeService.hpp"

#include "MsgUaServiceConfigReq.hpp"
#include "MsgUaEncodedMessageReceiveInd.hpp"

namespace app::ua::service
{

class UaService
{
public:
    UaService();

    ~UaService();

    void receive(MsgUaServiceConfigReq const&);
    void receive(MsgUaEncodedMessageReceiveInd const&);

    void subscribeService(DataTypeId, UaServiceInterfacePtr&&);

private:
    UaDiscoveryService discoverySrv;
    UaSessionService sessionSrv;
    UaAttributeService attributeSrv;
    std::map<DataTypeId, UaServiceInterfacePtr> services;
};

} // namespace app::ua::service
