#pragma once

#include "UtcTime.hpp"
#include "UInt32.hpp"
#include "StatusCode.hpp"
#include "String.hpp"
#include "DiagnosticInfo.hpp"

namespace app::ua
{

struct UascResponseHeader
{
    UtcTime                             timestamp;
    UInt32                              requestHandle;
    StatusCode                          serviceResult;
    DiagnosticInfo                      serviceDiagnostics;
    DynamicArray<String>                stringTable;
};

} // namespace app::ua
