add_subdirectory(common)
add_subdirectory(connector)
add_subdirectory(controller)
add_subdirectory(detector)
add_subdirectory(modbus)
add_subdirectory(ua)

add_executable(main
    Deployer.cpp
    main.cpp
)

target_link_libraries(main
    common
    connector
    detector
    modbus
    ua_transport
    ua_securechannel
    ua_service
    controller
)

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)