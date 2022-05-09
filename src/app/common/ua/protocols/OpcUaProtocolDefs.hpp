#pragma once

#include <cstdint>

namespace app::ua
{

static constexpr std::uint32_t opcUaProtocolVersion = 0;
static constexpr std::uint32_t opcUaSendBufferSize = 65536;
static constexpr std::uint32_t opcUaReceiveBufferSize = 65536;
static constexpr std::uint32_t opcUaMaxChunkCount = 5000;

} // namespace app::ua
