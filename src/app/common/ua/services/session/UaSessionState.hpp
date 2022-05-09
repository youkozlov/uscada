#pragma once

#include "Logger.hpp"
#include "UaCreateSessionReq.hpp"
#include "UaCloseSessionReq.hpp"
#include "UaActivateSessionReq.hpp"
#include "UaServiceHandler.hpp"

namespace app::ua
{

class UaSession;

class UaSessionState
{
public:
    ~UaSessionState() {}

    virtual char const* name() const = 0;

    virtual void onCreate(UaSession&, UaCreateSessionReq const&, UaServiceHandler) { LM(UA, LE, "Unexpected"); }

    virtual void onClose(UaSession&, UaCloseSessionReq const&, UaServiceHandler) { LM(UA, LE, "Unexpected"); }

    virtual void onActivate(UaSession&, UaActivateSessionReq const&, UaServiceHandler) { LM(UA, LE, "Unexpected"); }

    virtual void onEnter(UaSession&) {}

    virtual void onExit(UaSession&) {}

};

} // namespace app::ua
