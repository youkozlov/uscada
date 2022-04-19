add_library(modbus
    ModbusSession.cpp
    Modbus.cpp
)

target_include_directories(modbus PUBLIC
    ./
)

target_link_libraries(modbus
    common
)