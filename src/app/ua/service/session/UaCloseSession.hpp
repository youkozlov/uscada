#pragma once

#include "UaServiceInterface.hpp"

namespace app::ua::service
{

class UaSessionService;

class UaCloseSession : public UaServiceInterface
{
public:
    UaCloseSession(UaSessionService&);
    ~UaCloseSession();

    void receive(UaEncodedMessageHdr const&, OpcUaSduBuffer&) final;

private:
    UaSessionService& sessionService;
};

} // namespace app::ua::service