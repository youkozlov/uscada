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
    , modbusConfigReq
    , modbusConfigRsp
    , modbusDataReq
    , modbusDataInd
};

} // namespace app
