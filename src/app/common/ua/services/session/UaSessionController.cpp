#include "UaSessionController.hpp"
#include "UaCloseSessionReq.hpp"

namespace app::ua
{

UaSessionController::UaSessionController(reactor::ReactorInterface& reactor)
    : sessionPool("session", reactor, *this)
{
}

UaSessionController::~UaSessionController()
{
}

void UaSessionController::releaseSession(EntityId uid)
{
    sessionPool.release(uid);
}

void UaSessionController::receive(UaCreateSessionReq const& req, UaServiceHandler handler)
{
    EntityId uid;
    if (not sessionPool.alloc(uid))
    {
        LM(UA, LE, "Can not alloc session");
        return;
    }
    auto& session = sessionPool.get(uid);
    session.getState().onCreate(session, req, handler);
}

void UaSessionController::receive(UaCloseSessionReq const& req, UaServiceHandler handler)
{
    auto& nodeId = req.requestHdr.authentificationToken;
    if (std::holds_alternative<UInt32>(nodeId.value))
    {
        EntityId uid = (std::get<UInt32>(nodeId.value) & ~0xFFFF8000u);
        auto& session = sessionPool.get(uid);
        session.getState().onClose(session, req, handler);
    }
    else
    {
        LM(UA, LE, "Unexpected nodeId format");
    }
}

void UaSessionController::receive(UaActivateSessionReq const& req, UaServiceHandler handler)
{
    auto& nodeId = req.requestHdr.authentificationToken;
    if (std::holds_alternative<UInt32>(nodeId.value))
    {
        EntityId uid = (std::get<UInt32>(nodeId.value) & ~0xFFFF8000u);
        auto& session = sessionPool.get(uid);
        session.getState().onActivate(session, req, handler);
    }
    else
    {
        LM(UA, LE, "Unexpected nodeId format");
    }
}

void UaSessionController::cancel()
{
}

} // namespace app::ua
