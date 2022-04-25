add_library(controller
    modbus/ModbusTestController.cpp
    modbus/ModbusTestFsm.cpp
    modbus/ModbusTestInit.cpp
    modbus/ModbusTestConfigure.cpp
    modbus/ModbusTestSetup.cpp
    modbus/ModbusTestRun.cpp

    ControllerComponent.cpp
)

target_include_directories(controller PUBLIC
    .
    modbus
)

target_link_libraries(controller
    common
)