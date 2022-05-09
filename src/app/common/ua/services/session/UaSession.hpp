#pragma once

#include "FsmBase.hpp"
#include "UaSessionState.hpp"
#include "EntityId.hpp"
#include "ReactorInterface.hpp"
#include "UaSessionReleaser.hpp"

namespace app::ua
{

class UaSession : public app::FsmBase<UaSession, UaSessionState>
{
public:
    enum class Result
    {
          sucess
        , fail
    };
    explicit UaSession(EntityId, reactor::ReactorInterface&, UaSessionReleaser&);

    ~UaSession();

    void release();

    Result create(UaCreateSessionReq const&, UaServiceHandler);

    Result activate(UaActivateSessionReq const&, UaServiceHandler);

    Result close(UaCloseSessionReq const&, UaServiceHandler);

private:

    EntityId const uid;
    UaSessionReleaser& sessionReleaser;
};

} // namespace app::ua