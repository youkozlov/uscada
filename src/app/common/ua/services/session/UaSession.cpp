#include "UaSession.hpp"
#include "UaSessionInit.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaCreateSessionReq.hpp"
#include "UaCreateSessionRsp.hpp"
#include "TimeUtils.hpp"

namespace app::ua
{

UaSession::UaSession(EntityId uid_, reactor::ReactorInterface&, UaSessionReleaser& releaser)
    : FsmBase(&app::getSingleton<UaSessionInit>(), "UaSession")
    , uid(uid_)
    , sessionReleaser(releaser)
{
}

UaSession::~UaSession()
{
}

void UaSession::release()
{
    sessionReleaser.releaseSession(uid);
}

UaSession::Result UaSession::create(UaCreateSessionReq const& req, UaServiceHandler handler)
{
    UaCreateSessionRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.requestHdr.requestHandle;
    rsp.msg.sessionId.value.emplace<UInt32>(0x8000 + uid);
    rsp.msg.authenticationToken.value.emplace<UInt32>(0x8000 + uid);
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
    handler(tx);
    return Result::sucess;
}

UaSession::Result UaSession::activate(UaActivateSessionReq const& req, UaServiceHandler handler)
{
    UaActivateSessionRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.requestHdr.requestHandle;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    codec << rsp;
    handler(tx);
    return Result::sucess;
}

UaSession::Result UaSession::close(UaCloseSessionReq const& req, UaServiceHandler handler)
{
    UaCloseSessionRspCont rsp;
    rsp.msg.responseHdr.timestamp = utils::getCurrentDateTime();
    rsp.msg.responseHdr.requestHandle = req.requestHdr.requestHandle;

    OpcUaSduBuffer tx;
    OpcUaBinaryCodec codec(tx);
    codec << rsp;
    handler(tx);
    return Result::sucess;
}

} // namespace app::ua
