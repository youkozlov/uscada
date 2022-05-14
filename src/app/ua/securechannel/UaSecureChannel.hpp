#pragma once

#include "MsgUaSecureChannelConfigReq.hpp"
#include "MsgUaOpenSecureChannelReq.hpp"
#include "MsgUaCloseSecureChannelReq.hpp"
#include "MsgUaAssociateSecureChannelReq.hpp"
#include "MsgUaSecuredMessageReceiveInd.hpp"
#include "MsgUaEncodedMessageSendReq.hpp"
#include "MsgUaConnectionReleaseInd.hpp"

#include "ReleaserInterface.hpp"
#include "UaServerSecureChannel.hpp"
#include "UaEntityPool.hpp"

namespace app::ua::securechannel
{

class UaSecureChannel : public ReleaserInterface
{
public:
    UaSecureChannel();

    ~UaSecureChannel();

    void receive(MsgUaSecureChannelConfigReq const&);
    void receive(MsgUaOpenSecureChannelReq const&);
    void receive(MsgUaCloseSecureChannelReq const&);
    void receive(MsgUaAssociateSecureChannelReq const&);
    void receive(MsgUaSecuredMessageReceiveInd const&);
    void receive(MsgUaEncodedMessageSendReq const&);
    void receive(MsgUaConnectionReleaseInd const&);

private:
    void release(UaSecureChannelId) final;

    UaEntityPool<UaServerSecureChannel> serverSecureChannelPool;
};

} // namespace app::ua::securechannel
