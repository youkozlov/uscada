#include "UaSessionService.hpp"
#include "UaCreateSession.hpp"
#include "UaCloseSession.hpp"
#include "UaActivateSession.hpp"
#include "UaService.hpp"

namespace app::ua::service
{

UaSessionService::UaSessionService(reactor::ReactorInterface& reactor)
    : sessionPool("session", reactor, *this)

{
}

UaSessionService::~UaSessionService()
{
}

void UaSessionService::subscribe(UaService& service)
{
    service.subscribeService(DataTypeId::CreateSessionRequest_Encoding_DefaultBinary, std::make_unique<UaCreateSession>(*this));
    service.subscribeService(DataTypeId::CloseSessionRequest_Encoding_DefaultBinary, std::make_unique<UaCloseSession>(*this));
    service.subscribeService(DataTypeId::ActivateSessionRequest_Encoding_DefaultBinary, std::make_unique<UaActivateSession>(*this));
}

void UaSessionService::release(UaSessionId uid)
{
    sessionPool.release(uid);
}

void UaSessionService::receive(UaEncodedMessageHdr const& hdr, UaCreateSessionReq const& msg)
{
    UaSessionId uid;
    if (not sessionPool.alloc(uid))
    {
        LM(UASRV, LD, "Can not alloc session");
        return;
    }
    auto& session = sessionPool.get(uid);
    session.getState().onReceive(session, hdr, msg);
}

void UaSessionService::receive(UaEncodedMessageHdr const& hdr, UaActivateSessionReq const& msg)
{
    auto& nodeId = msg.requestHdr.authentificationToken;
    if (std::holds_alternative<UInt32>(nodeId.value))
    {
        EntityId uid = (std::get<UInt32>(nodeId.value));
        auto& session = sessionPool.get(uid);
        session.getState().onReceive(session, hdr, msg);
    }
    else
    {
        LM(UASRV, LE, "Unexpected nodeId format");
    }
}

void UaSessionService::receive(UaEncodedMessageHdr const& hdr, UaCloseSessionReq const& msg)
{
    auto& nodeId = msg.requestHdr.authentificationToken;
    if (std::holds_alternative<UInt32>(nodeId.value))
    {
        EntityId uid = (std::get<UInt32>(nodeId.value));
        auto& session = sessionPool.get(uid);
        session.getState().onReceive(session, hdr, msg);
    }
    else
    {
        LM(UASRV, LE, "Unexpected nodeId format");
    }
}

void UaSessionService::receive(UaEncodedMessageHdr const& hdr, UaServiceHandler const& handler)
{
    if (invalidSuid == hdr.sessionId)
    {
        LM(UASRV, LE, "Unexpected sessionId");
        return;
    }
    auto& session = sessionPool.get(hdr.sessionId);
    session.getState().onReceive(session, hdr, handler);
}


} // namespace app::ua::service
