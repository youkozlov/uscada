#pragma once

#include "UaCreateSessionReq.hpp"
#include "UaActivateSessionReq.hpp"
#include "UaCloseSessionReq.hpp"
#include "UaEncodedMessageHdr.hpp"
#include "ReleaserInterface.hpp"
#include "ReactorInterface.hpp"
#include "UaSession.hpp"
#include "UaEntityPool.hpp"
#include "UaSessionId.hpp"

namespace app::ua::service
{

class UaService;

class UaSessionService : public ReleaserInterface
{
public:
    UaSessionService(reactor::ReactorInterface&);
    ~UaSessionService();

    void subscribe(UaService&);

    void receive(UaEncodedMessageHdr const&, UaCreateSessionReq const&);
    void receive(UaEncodedMessageHdr const&, UaActivateSessionReq const&);
    void receive(UaEncodedMessageHdr const&, UaCloseSessionReq const&);
    void receive(UaEncodedMessageHdr const&, UaServiceHandler const&);

private:
    void release(UaSessionId) final;

    UaEntityPool<UaSession> sessionPool;
};

} // namespace app::ua::service
