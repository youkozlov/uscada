#pragma once

#include "UtcTime.hpp"
#include "UInt32.hpp"
#include "StatusCode.hpp"
#include "String.hpp"
#include "DiagnosticInfo.hpp"
#include "UaAdditionalHeader.hpp"

namespace app::ua
{

struct UaResponseHeader
{
    UtcTime                             timestamp;
    UInt32                              requestHandle;
    StatusCode                          serviceResult;
    DiagnosticInfo                      serviceDiagnostics;
    DynamicArray<String>                stringTable;
    UaAdditionalHeader                  additionalHeader;
};

} // namespace app::ua
