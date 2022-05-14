#pragma once

#include <optional>

#include "FsmBase.hpp"
#include "UaSessionState.hpp"
#include "UaSessionId.hpp"
#include "ReactorInterface.hpp"
#include "ReleaserInterface.hpp"

namespace app::ua::service
{

class UaSession : public app::FsmBase<UaSession, UaSessionState>
{
public:
    enum class Result
    {
          sucess
        , fail
    };
    explicit UaSession(UaSessionId, reactor::ReactorInterface&, ReleaserInterface&);

    ~UaSession();

    void release();

    Result receive(UaEncodedMessageHdr const&, UaCreateSessionReq const&);
    Result receive(UaEncodedMessageHdr const&, UaActivateSessionReq const&);
    Result receive(UaEncodedMessageHdr const&, UaCloseSessionReq const&);
    Result receive(UaEncodedMessageHdr const&, UaServiceHandler const&);

private:

    UaSessionId const sessionId;
    std::optional<UaSecureChannelId> secureChannelId;
    ReleaserInterface& sessionReleaser;
};

} // namespace app::ua::service