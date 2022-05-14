#pragma once

#include "UaServiceInterface.hpp"

namespace app::ua::service
{

class UaSessionService;

class UaActivateSession : public UaServiceInterface
{
public:
    UaActivateSession(UaSessionService&);
    ~UaActivateSession();

    void receive(UaEncodedMessageHdr const&, OpcUaSduBuffer&) final;

private:
    UaSessionService& sessionService;
};

} // namespace app::ua::service
