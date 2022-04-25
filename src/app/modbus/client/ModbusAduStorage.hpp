#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include "Queue.hpp"
#include "AduRequest.hpp"
#include "ModbusDefs.hpp"

namespace app::modbus
{

class ModbusAduStorage
{
public:
    ModbusAduStorage();

    ~ModbusAduStorage();

    ModbusAduStorage(ModbusAduStorage&) = delete;

    ModbusAduStorage& operator=(ModbusAduStorage&) = delete;

    bool push(AduRequest const&);

    AduRequest const& front();

    void pop();

    bool empty() const;

private:
    static constexpr unsigned capacity = 64;
    static constexpr unsigned bufferSize = capacity * maxAduLen;

    app::Queue<unsigned> freeIds;
    app::Queue<unsigned> busyIds;
    std::vector<AduRequest> adus;
    std::array<std::uint8_t, bufferSize> buffer;
};

} // namespace app::modbus
