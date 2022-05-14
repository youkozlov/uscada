#pragma once

#include <optional>

#include "FsmBase.hpp"
#include "ReleaserInterface.hpp"
#include "ReactorInterface.hpp"

#include "UaServerSecureChannelState.hpp"
#include "MsgUaOpenSecureChannelReq.hpp"
#include "MsgUaCloseSecureChannelReq.hpp"
#include "MsgUaSecuredMessageReceiveInd.hpp"
#include "MsgUaEncodedMessageSendReq.hpp"
#include "MsgUaConnectionReleaseInd.hpp"

namespace app::ua::securechannel
{

class UaServerSecureChannel : public app::FsmBase<UaServerSecureChannel, UaServerSecureChannelState>
{
public:
    enum class Result
    {
          done
        , error
    };
    explicit UaServerSecureChannel(EntityId, reactor::ReactorInterface&, ReleaserInterface&);

    ~UaServerSecureChannel();

    Result receive(MsgUaOpenSecureChannelReq const&);
    Result receive(MsgUaCloseSecureChannelReq const&);
    Result receive(MsgUaAssociateSecureChannelReq const&);
    Result receive(MsgUaSecuredMessageReceiveInd const&);
    Result receive(MsgUaEncodedMessageSendReq const&);

    void   release();
    void   sendUaConnectionReleaseReq(UaConnectionId);

private:

    void acceptConnection(reactor::LinkPtr&);
    void closeConnection();
    Result receiveOpenSecureChannelReq();
    Result receiveCloseSecureChannelReq();
    Result receiveSecureChannelReq();

    UaSecureChannelId const secureChannelId;
    reactor::ReactorInterface& reactor;
    ReleaserInterface& releaser;

    std::uint32_t sequenceNumberTx{1};
    std::uint32_t storedRxSequenceNumber;
    std::uint32_t storedRequestId;
    std::uint32_t storedRequestedLifetime;
    std::uint32_t storedTokenId;
    std::optional<UaConnectionId> connectionId;
    std::optional<UaSessionId>    sessionId;
};

} // namespace app::ua::securechannel
