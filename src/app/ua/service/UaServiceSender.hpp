#pragma once

#include "SenderBase.hpp"

#include "MsgUaServiceInitRsp.hpp"
#include "MsgUaServiceConfigRsp.hpp"
#include "MsgUaServiceReleaseRsp.hpp"
#include "MsgUaEncodedMessageSendReq.hpp"

namespace app::ua::service
{

class Sender : public reactor::SenderBase<Sender>
{
public:
    virtual ~Sender() {}

    virtual void send(MsgUaServiceInitRsp const&) = 0;
    virtual void send(MsgUaServiceConfigRsp const&) = 0;
    virtual void send(MsgUaServiceReleaseRsp const&) = 0;
    virtual void send(MsgUaEncodedMessageSendReq const&) = 0;
};

} // namespace app::ua::service
