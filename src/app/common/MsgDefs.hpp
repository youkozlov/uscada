#pragma once

#include "MsgInterface.hpp"

namespace app
{

enum MsgIds : reactor::MsgId
{
      controllerStartReq = 0
    , controllerStopReq

    , connectorInitReq
    , connectorInitRsp

    , detectorInitReq
    , detectorInitRsp

    , modbusInitReq
    , modbusInitRsp
    , modbusReleaseReq
    , modbusReleaseRsp
    , modbusConfigReq
    , modbusConfigRsp
    , modbusClientAduReq
    , modbusClientAduRsp
    , modbusAduReq
    , modbusAduRsp
};

} // namespace app
