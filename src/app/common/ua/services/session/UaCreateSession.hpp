#pragma once

#include "UaServiceInterface.hpp"
#include "OpcUaSecureChannel.hpp"

namespace app::ua
{

class UaSessionController;

class UaCreateSession : public UaServiceInterface
{
public:
    UaCreateSession(UaSessionController&);
    ~UaCreateSession();

    void process(OpcUaSecureChannel&) final;

private:
    UaSessionController& sessionController;
    std::uint32_t storedRequestHandle;
};

} // namespace app::ua
