#pragma once

#include "UaServiceInterface.hpp"
#include "OpcUaSecureChannel.hpp"

namespace app::ua
{

class UaSessionController;

class UaCloseSession : public UaServiceInterface
{
public:
    UaCloseSession(UaSessionController&);
    ~UaCloseSession();

    void process(OpcUaSecureChannel&) final;

private:
    UaSessionController& sessionController;
    std::uint32_t storedRequestHandle;
};

} // namespace app::ua
