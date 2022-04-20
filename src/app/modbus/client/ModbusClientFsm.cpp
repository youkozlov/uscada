#include "ModbusClientFsm.hpp"
#include "ModbusClientInit.hpp"
#include "ModbusClient.hpp"

namespace app
{

ModbusClientFsm::ModbusClientFsm(ModbusClient& entity_)
    : state(&getSingleton<ModbusClientInit>())
    , entity(entity_)
{
}

ModbusClientFsm::~ModbusClientFsm()
{
}

ModbusClientState& ModbusClientFsm::getState()
{
    return *state;
}

void ModbusClientFsm::startTimer()
{
    entity.startTimer();
}

void ModbusClientFsm::stopTimer()
{
    entity.stopTimer();
}

void ModbusClientFsm::connect()
{
    entity.connect();
}

int ModbusClientFsm::send()
{
    return entity.send();
}

int ModbusClientFsm::receive()
{
    return entity.receive();
}

void ModbusClientFsm::close()
{
    entity.close();
}

} // namespace app
