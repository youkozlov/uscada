#pragma once

#include <optional>

#include "FsmBase.hpp"
#include "UaConnectionId.hpp"
#include "LinkPtr.hpp"
#include "TimerPtr.hpp"
#include "ReactorInterface.hpp"
#include "ReleaserInterface.hpp"
#include "OpcUaSduBuffer.hpp"
#include "UaTcpConnectionState.hpp"
#include "UaConnectionId.hpp"

#include "MsgUaOpenSecureChannelRsp.hpp"
#include "MsgUaCloseSecureChannelRsp.hpp"
#include "MsgUaSecuredMessageSendReq.hpp"
#include "MsgUaConnectionReleaseReq.hpp"

namespace app::ua::transport
{

class UaTcpConnection : public app::FsmBase<UaTcpConnection, UaTcpConnectionState>
{
public:
    enum class Result
    {
          noerror
        , done
        , error
    };

    explicit UaTcpConnection(UaConnectionId, reactor::ReactorInterface&, ReleaserInterface&);

    ~UaTcpConnection();

    Result receive(MsgUaOpenSecureChannelRsp const&);
    Result receive(MsgUaCloseSecureChannelRsp const&);
    Result receive(MsgUaSecuredMessageSendReq const&);
    void receive(MsgUaConnectionReleaseReq const&);
    void acceptLink(reactor::LinkPtr&);

    // common
    void release();
    void allocTimer();
    void startTimer(long);
    void stopTimer();
    void receivePreaction();
    Result receive();
    Result receiveHello();
    Result sendAcknowledge();
    Result receiveSecuredMessage();
    void sendUaConnectionReleaseInd();
private:

    UaConnectionId const connectionId;
    reactor::ReactorInterface& reactor;
    ReleaserInterface& releaser;
    reactor::LinkPtr link;
    reactor::TimerPtr timer;
    OpcUaSduBuffer rxBuffer;
    std::optional<UaSecureChannelId> associatedSecureChannelId;
};

} // namespace app::ua::transport
