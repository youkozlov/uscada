#pragma once

#include <cstdint>

namespace app::modbus
{
static constexpr unsigned modbusProtocolId = 0x0;
static constexpr unsigned numBytesLen = 1;
static constexpr unsigned pduFuncCodeLen = 1;
static constexpr unsigned pduMaxDataLen = 252;
static constexpr unsigned maxPduLen = pduFuncCodeLen + pduMaxDataLen;
static constexpr unsigned aduTransactIdLen = 2;
static constexpr unsigned aduProtocolIdLen = 2;
static constexpr unsigned aduPacketLen = 2;
static constexpr unsigned aduAddressLen = 1;
static constexpr unsigned maxAduLen = aduTransactIdLen + aduProtocolIdLen + aduPacketLen + aduAddressLen + maxPduLen;
static constexpr uint16_t minAddr = 0;
static constexpr uint16_t maxAddr = 247;

} // namespace app::modbus
