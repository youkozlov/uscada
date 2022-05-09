#pragma once

#include "UaEntityPool.hpp"
#include "UaSession.hpp"
#include "ReactorInterface.hpp"
#include "UaSessionReleaser.hpp"
#include "UaServiceHandler.hpp"
#include "UaCreateSessionReq.hpp"
#include "UaCloseSessionReq.hpp"
#include "UaActivateSessionReq.hpp"

namespace app::ua
{

class UaSessionController : public UaSessionReleaser
{
public:
    UaSessionController(reactor::ReactorInterface&);
    ~UaSessionController();

    void receive(UaCreateSessionReq const&, UaServiceHandler);
    void receive(UaCloseSessionReq const&, UaServiceHandler);
    void receive(UaActivateSessionReq const&, UaServiceHandler);
    void cancel();

private:
    void releaseSession(EntityId) final;

    UaEntityPool<UaSession> sessionPool;
};

} // namespace app::ua
