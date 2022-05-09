#pragma once

#include "UaServiceInterface.hpp"
#include "OpcUaSecureChannel.hpp"

namespace app::ua
{

class UaSessionController;

class UaActivateSession : public UaServiceInterface
{
public:
    UaActivateSession(UaSessionController&);
    ~UaActivateSession();

    void process(OpcUaSecureChannel&) final;

private:
    UaSessionController& sessionController;
    std::uint32_t storedRequestHandle;
};

} // namespace app::ua
