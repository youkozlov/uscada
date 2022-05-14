#pragma once

#include "UaServiceInterface.hpp"

namespace app::ua::service
{

class UaSessionService;

class UaCreateSession : public UaServiceInterface
{
public:
    UaCreateSession(UaSessionService&);
    ~UaCreateSession();

    void receive(UaEncodedMessageHdr const&, OpcUaSduBuffer&) final;

private:
    UaSessionService& sessionService;
};

} // namespace app::ua::service
