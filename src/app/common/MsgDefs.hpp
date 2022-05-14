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

    , uaTransportInitReq
    , uaTransportInitRsp
    , uaTransportReleaseReq
    , uaTransportReleaseRsp
    , uaTransportConfigReq
    , uaTransportConfigRsp
    , uaSecuredMessageSendReq
    , uaSecuredMessageReceiveInd
    , uaConnectionReleaseReq
    , uaConnectionReleaseInd

    , uaSecureChannelInitReq
    , uaSecureChannelInitRsp
    , uaSecureChannelReleaseReq
    , uaSecureChannelReleaseRsp
    , uaSecureChannelConfigReq
    , uaSecureChannelConfigRsp
    , uaOpenSecureChannelReq
    , uaOpenSecureChannelRsp
    , uaCloseSecureChannelReq
    , uaCloseSecureChannelRsp
    , uaAssociateSecureChannelReq
  
    , uaServiceInitReq
    , uaServiceInitRsp
    , uaServiceReleaseReq
    , uaServiceReleaseRsp
    , uaServiceConfigReq
    , uaServiceConfigRsp
    , uaEncodedMessageSendReq
    , uaEncodedMessageReceiveInd

};

} // namespace app
