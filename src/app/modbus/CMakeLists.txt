add_library(modbus
    client/ModbusClient.cpp
    client/ModbusClientFsm.cpp
    client/ModbusClientInit.cpp
    client/ModbusClientConnect.cpp
    client/ModbusClientConnected.cpp
    client/ModbusClientReceive.cpp
    client/ModbusClientBackoff.cpp
    client/ModbusTransactionStorage.cpp
    server/ModbusServer.cpp
    server/ModbusSession.cpp
    server/ModbusAduPool.cpp
    server/ModbusSessionPool.cpp
    ModbusCodec.cpp
    Modbus.cpp
    ModbusComponent.cpp
)

target_include_directories(modbus PUBLIC
    .
    client
    server
)

target_link_libraries(modbus
    common
)