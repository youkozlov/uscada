#pragma once

#include "Logger.hpp"
#include "UaCreateSessionReq.hpp"
#include "UaCloseSessionReq.hpp"
#include "UaActivateSessionReq.hpp"
#include "UaServiceInterface.hpp"

namespace app::ua::service
{

class UaSession;

class UaSessionState
{
public:
    ~UaSessionState() {}

    virtual char const* name() const = 0;

    virtual void onReceive(UaSession&, UaEncodedMessageHdr const&, UaCreateSessionReq const&) { LM(UASRV, LE, "Unexpected"); }

    virtual void onReceive(UaSession&, UaEncodedMessageHdr const&, UaCloseSessionReq const&) { LM(UASRV, LE, "Unexpected"); }

    virtual void onReceive(UaSession&, UaEncodedMessageHdr const&, UaActivateSessionReq const&) { LM(UASRV, LE, "Unexpected"); }

    virtual void onEnter(UaSession&) {}

    virtual void onExit(UaSession&) {}

};

} // namespace app::ua::service
