add_library(modbus
    client/ModbusClient.cpp
    client/ModbusClientFsm.cpp
    client/ModbusClientInit.cpp
    client/ModbusClientConnect.cpp
    client/ModbusClientConnected.cpp
    client/ModbusClientSend.cpp
    client/ModbusClientReceive.cpp
    client/ModbusClientBackoff.cpp
    client/ModbusAduStorage.cpp
    server/ModbusServer.cpp
    server/session/ModbusSession.cpp
    server/session/ModbusSessionFsm.cpp
    server/session/ModbusSessionInit.cpp
    server/session/ModbusSessionConnected.cpp
    server/session/ModbusSessionWaitModbusAduRsp.cpp
    server/ModbusSessionPool.cpp
    ModbusCodec.cpp
    Modbus.cpp
    ModbusComponent.cpp
)

target_include_directories(modbus PUBLIC
    .
    client
    server
    server/session
)

target_link_libraries(modbus
    common
)