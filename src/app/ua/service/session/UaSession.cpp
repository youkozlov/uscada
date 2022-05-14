#include "UaSession.hpp"
#include "UaSessionInit.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaCreateSessionReq.hpp"
#include "UaCreateSessionRsp.hpp"
#include "UaServiceSender.hpp"
#include "TimeUtils.hpp"

namespace app::ua::service
{

UaSession::UaSession(EntityId uid_, reactor::ReactorInterface&, ReleaserInterface& releaser)
    : FsmBase(&app::getSingleton<UaSessionInit>(), "UaSession")
    , sessionId(uid_)
    , sessionReleaser(releaser)
{
}

UaSession::~UaSession()
{
}

void UaSession::release()
{
    secureChannelId = {};
    sessionReleaser.release(sessionId);
}

UaSession::Result UaSession::receive(UaEncodedMessageHdr const& hdr, UaCreateSessionReq const& req)
{
    UaCreateSessionRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.requestHdr.requestHandle;
    rsp.msg.sessionId.value.emplace<UInt32>(sessionId);
    rsp.msg.authenticationToken.value.emplace<UInt32>(sessionId);
    rsp.msg.revisedSessionTimeout = req.requestedSessionTimeout;
    auto& descr = rsp.msg.serverEndpoints.emplace_back();
    descr.endpointUrl = "opc.tcp://localhost:4369";
    descr.server.applicationUri = "urn:youkozlov-VivoBook-ASUSLaptop-X513EAN-K513EA:uscada";
    descr.server.productUri = "urn:uscada";
    descr.securityMode = toInt32(UaSecurityModeEnum::none);
    descr.securityPolicyUri = "http://opcfoundation.org/UA/SecurityPolicy#None";
    rsp.msg.maxRequestMessageSize = req.maxResponseMessageSize;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    codec << rsp;

    reactor::MsgStore<MsgUaEncodedMessageSendReq> msgStore;
    auto& msgRsp = msgStore.getMsg();
    msgRsp.hdr = hdr;
    msgRsp.length = tx.size();
    std::memcpy(&msgRsp.data[0], tx.begin(), tx.size());
    Sender::sendMsg(msgStore);
    return Result::sucess;
}

UaSession::Result UaSession::receive(UaEncodedMessageHdr const& hdr, UaActivateSessionReq const& req)
{
    UaActivateSessionRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.requestHdr.requestHandle;

    {
        secureChannelId = hdr.secureChannelId;
        reactor::MsgStore<MsgUaAssociateSecureChannelReq> msgStore;
        auto& msgRsp = msgStore.getMsg();
        msgRsp.hdr = hdr;
        msgRsp.hdr.sessionId = sessionId;
        Sender::sendMsg(msgStore);
    }

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    codec << rsp;

    reactor::MsgStore<MsgUaEncodedMessageSendReq> msgStore;
    auto& msgRsp = msgStore.getMsg();
    msgRsp.hdr = hdr;
    msgRsp.hdr.sessionId = sessionId;
    msgRsp.length = tx.size();
    std::memcpy(&msgRsp.data[0], tx.begin(), tx.size());
    Sender::sendMsg(msgStore);
    return Result::sucess;
}

UaSession::Result UaSession::receive(UaEncodedMessageHdr const& hdr, UaCloseSessionReq const& req)
{
    UaCloseSessionRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.requestHdr.requestHandle;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    codec << rsp;

    reactor::MsgStore<MsgUaEncodedMessageSendReq> msgStore;
    auto& msgRsp = msgStore.getMsg();
    msgRsp.hdr = hdr;
    msgRsp.length = tx.size();
    std::memcpy(&msgRsp.data[0], tx.begin(), tx.size());
    Sender::sendMsg(msgStore);
    return Result::sucess;
}

UaSession::Result UaSession::receive(UaEncodedMessageHdr const& hdr, UaServiceHandler const& handler)
{
    if (not secureChannelId || *secureChannelId != hdr.secureChannelId)
    {
        LM(UASRV, LE, "Uid=%u, unexpected secure channel Id", sessionId);
        return Result::fail;
    }
    handler();
    return Result::sucess;
}

} // namespace app::ua::service
